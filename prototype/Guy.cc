//  $Id: Guy.cc,v 1.29 2001/08/22 10:19:10 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "View.hh"
#include "GuileAdventObj.hh"
#include "Advent.hh"
#include "Scenario.hh"
#include "ScenarioSmob.hh"
#include "Guy.hh"

long Guy::tag;
Guy* Guy::current_person;

Guy::Guy (SCM p)
  : scm_object (p),
    scenario (0)
{
  click_manager.add (this);

  std::cout << "Creating person: " << this << std::endl;
  scm_protect_object (scm_object);

  // FIXME: Missing error checking...
  SCM gfx = gh_call1(gh_lookup("gfx"), scm_object);
  set_gfx (gfx);

  sur_angry = CL_Surface ("emo_angry", app.get_resource ());
  sur_questioning = CL_Surface ("emo_questioning", app.get_resource ());

  counter = 0;
  pos.x = 330;
  pos.y = 355;
  target = pos;
  delta = 4.0;
  emotion = NORMAL;

  target_callback = SCM_BOOL_F;
  target_hook     = SCM_BOOL_F;

  scm_protect_object (target_callback);

  scenario = 0;
  current_person = this;
}

Guy::~Guy ()
{
}

void
Guy::update (float delta)
{
  // update animation
  if (target != pos)
    {
      counter += delta * 10.0f;
      if (counter >= 7.0f)
	counter = 0;

      if (on_target ())
	{
	  target = pos;
	}
      else
	{
	  CL_Vector tmp_pos = pos + (direction*delta*20.0);
	  if (scenario->get_colmap ()->get_pixel (int(tmp_pos.x), int(tmp_pos.y)) != 0)
	    {
	      pos = tmp_pos;
	      pos.z = scenario->get_colmap ()->get_pixel (int(pos.x), int(pos.y));
	    }
	  else
	    {
	      target = pos;
	    }
	}
    }
  else // target == pos
    {
      SCM tmp_hook = target_hook;

      if (target_callback != SCM_BOOL_F)
	{
	  SCM tmp_callback = target_callback;

	  gh_call0 (target_callback);
	  //scm_unprotect_object (target_callback);

	  // We need to check that the callback is still the same,
	  // since it could have been changed in the callback
	  if (tmp_callback == target_callback) {
	    target_callback = SCM_BOOL_F;
	    scm_protect_object (target_callback);
	  }
	}

      if (target_hook != SCM_BOOL_F && tmp_hook == target_hook)
	{
	  SCM tmp_hook = target_hook;

	  AdvHook::call_finish (tmp_hook);

	  if (tmp_hook == target_hook) {
	    scm_unprotect_object (target_hook);
	    target_hook = SCM_BOOL_F;
	  }
	}

      counter = 0;
    }
}

bool
Guy::on_target ()
{
  if (pos.x - delta < target.x
      && pos.x + delta > target.x
      && pos.y - delta < target.y
      && pos.y + delta > target.y)
    {
      return true;
    }
  return false;
}

void
Guy::draw_world (int x_offset = 0, int y_offset = 0)
{
  float zoom = scenario->get_colmap ()->get_pixel (pos.x, pos.y) / 255.0;

  CL_Surface* sur;

  if (fabs(direction.x) < fabs(direction.y))
    {
      if (direction.y > 0)
	sur = &sur_front;
      else
	sur = &sur_back;
    }
  else
    {
      if (direction.x > 0)
	sur = &sur_right;
      else
	sur = &sur_left;
    }

  sur->put_screen (pos.x - (sur->get_width ()/2 * zoom) + x_offset,
		   pos.y - (sur->get_height () * zoom) + y_offset,
		   zoom, zoom, int(counter) % sur->get_num_frames ());

  if (this == current_person)
    sur_questioning.put_screen(pos.x - (8*zoom) + x_offset,
			       pos.y  + y_offset);

  switch (emotion)
    {
    case ANGRY:
      sur_angry.put_screen(pos.x - (8* zoom) + x_offset,
			   pos.y - ((sur->get_height ()+20) * zoom) + y_offset);
      break;
    case QUESTIONING:
      sur_questioning.put_screen(pos.x - (8*zoom) + x_offset,
				 pos.y - ((sur->get_height ()+20) * zoom) + y_offset);
      break;
    default:
      break;
    }
}

CL_Vector
Guy::transform_to_walkable (CL_Vector pos)
{
  CollisionMap* colmap = Scenario::get_current ()->get_colmap ();
  int maxtop = -1;
  int maxbottom = -1;

  for (int i = (int) pos.y; i >= 0; --i)
    if (colmap->get_pixel (pos.x, i))
      {
	maxtop = i;
	break;
      }

  for (int i = (int)pos.y; i < 480; ++i)
    if (colmap->get_pixel (pos.x, i) != 0)
      {
	maxbottom = i;
	break;
      }

  //std::cout << "Top:    " << maxtop - pos.y << std::endl;
  //std::cout << "Bottom: " << maxbottom - pos.y << std::endl;

  if (maxbottom == -1 && maxtop == -1)
    return pos;
  else if (maxtop == -1)
    return CL_Vector (pos.x, maxbottom);
  else if (maxbottom == -1)
    return CL_Vector (pos.x, maxtop);
  else
    {
      if (pos.y - maxtop > maxbottom - pos.y)
	return CL_Vector (pos.x, maxbottom);
      else
	return CL_Vector (pos.x, maxtop);
    }
}

void
Guy::walk_to_mouse ()
{
  CL_Vector key(CL_Mouse::get_x (), CL_Mouse::get_y ());

  key -= CL_Vector (the_view->x_offset, the_view->y_offset);

  std::cout << "MousePos: " << key << std::endl;

  AdventObj* obj = Scenario::get_current ()->get_object (CL_Mouse::get_x (), CL_Mouse::get_y ());

  if (obj)
    {
      GuileAdventObj* guile_obj = dynamic_cast<GuileAdventObj*>(obj);

      // FIXME: Ugly way to find out if adv:walk is overloaded for guile_obj
      if (guile_obj && (guile_obj->call ("adv:walk") == SCM_BOOL_F))
	{
	  // Walk to the given position
	  direction = CL_Vector (key.x - pos.x,
				 key.y - pos.y);
	  direction.normalize ();
	  direction *= 5.0;
	  target = CL_Vector (key.x,
			      key.y);
	}
    }
  else
    {
      //std::cout << "Before: " << key << std::endl;
      key = transform_to_walkable (key);
      //std::cout << "After: " << key << std::endl;

      // Walk to the given position
      direction = CL_Vector (key.x - pos.x,
			     key.y - pos.y);
      direction.normalize ();
      direction *= 5.0;
      target = CL_Vector (key.x, key.y);
    }
}

bool
Guy::is_at (int x, int y)
{
  //std::cout << "isat: " << x << " " << y << std::endl;
  if (this == current_person)
    return false;

  float zoom = scenario->get_colmap ()->get_pixel (int(pos.x), int(pos.y)) / 255.0;

  if (pos.x - zoom*sur_left.get_width()/2 < x
      && pos.x + zoom*sur_left.get_width()/2 > x
      && pos.y > y
      && pos.y - zoom*sur_left.get_height () < y)
    {
      return true;
    }
  return false;
}

void
Guy::init_guile ()
{
  // getter
  gh_new_procedure0_0 ("c:guy:get-x-pos", &Guy::scm_get_x_pos);
  gh_new_procedure0_0 ("c:guy:get-y-pos", &Guy::scm_get_y_pos);
  gh_new_procedure0_0 ("c:guy:get-direction", &Guy::scm_get_direction);

  // setter
  gh_new_procedure2_0 ("c:guy:set-position", &Guy::scm_set_pos);
  gh_new_procedure1_0 ("c:guy:set-direction", &Guy::scm_set_direction);
  gh_new_procedure3_0 ("c:guy:set-target", &Guy::scm_set_target);
  gh_new_procedure1_0 ("c:guy:set-emotion", &Guy::scm_set_emotion);
  gh_new_procedure2_0 ("c:guy:set-scenario", &Guy::scm_set_scenario);
  gh_new_procedure2_0 ("c:guy:set-gfx", &Guy::scm_set_gfx);

  tag = scm_make_smob_type ("Person", // name for error mesg.
			    sizeof (Guy));

  scm_set_smob_mark  (tag, &mark_smob);
  scm_set_smob_free  (tag, &free_smob);
  scm_set_smob_print (tag, &print_smob);

  gh_new_procedure1_0 ("c:person:make", &Guy::make);
  gh_new_procedure1_0 ("c:person:set-current", &Guy::scm_set_current);
}

SCM
Guy::scm_set_pos (SCM arg_x_pos, SCM arg_y_pos)
{
  current_person->pos.x = SCM_INUM (arg_x_pos);
  current_person->pos.y = SCM_INUM (arg_y_pos);
  current_person->target = current_person->pos;
  return SCM_UNSPECIFIED;
}

SCM
Guy::scm_set_direction (SCM angle)
{
  switch (SCM_INUM (angle))
    {
    case 0: // up
      current_person->direction = CL_Vector (0., -5.);
      break;
    case 1: // right
      current_person->direction = CL_Vector (5., 0.);
      break;
    case 2: // down
      current_person->direction = CL_Vector (0., 5.);
      break;
    case 3: // left
      current_person->direction = CL_Vector (-5., 0.);
      break;
    }
  return SCM_UNSPECIFIED;
}

SCM
Guy::scm_set_target (SCM arg_x_pos, SCM arg_y_pos, SCM callback)
{
  current_person->direction = CL_Vector (SCM_INUM(arg_x_pos) - current_person->pos.x,
					 SCM_INUM (arg_y_pos) - current_person->pos.y);
  current_person->direction.normalize ();
  current_person->direction *= 5.0;
  current_person->target = CL_Vector (SCM_INUM(arg_x_pos), SCM_INUM (arg_y_pos));

  //scm_unprotect_object (current_person->target_callback);
  current_person->target_callback = callback;
  scm_protect_object (current_person->target_callback);

  //printf (" Target Pos: %f %f\n", current_person->target.x, current_person->target.y);

  current_person->target_hook = AdvHook::make ();
  scm_protect_object (current_person->target_hook);
  return current_person->target_hook;
}

SCM
Guy::scm_get_direction ()
{
  int direction = 0;
  if (fabs(current_person->direction.x) < fabs(current_person->direction.y))
    {
      if (current_person->direction.y > 0)
	direction = 2;
      else
	direction = 0;
    }
  else
    {
      if (current_person->direction.x > 0)
	direction = 1;
      else
	direction = 3;
    }

  return SCM_MAKINUM (direction);
}

SCM
Guy::scm_get_x_pos ()
{
  return SCM_MAKINUM (int(current_person->pos.x));
}

SCM
Guy::scm_get_y_pos ()
{
  return SCM_MAKINUM (int(current_person->pos.y));
}

SCM
Guy::scm_set_emotion (SCM num)
{
  switch (SCM_INUM (num))
    {
    case NORMAL:
      current_person->emotion = NORMAL;
      break;
    case ANGRY:
      current_person->emotion = ANGRY;
      break;
    case QUESTIONING:
      current_person->emotion = QUESTIONING;
      break;
    default:
      std::cout << "Unknown emotion" << std::endl;
      break;
    }
  return SCM_UNSPECIFIED;
}

void
Guy::mark ()
{

}

SCM
Guy::make (SCM person)
{
  Guy* guy = new Guy (person);
  SCM_RETURN_NEWSMOB (tag, guy);
}

SCM
Guy::mark_smob (SCM smob)
{
  Guy* guy = reinterpret_cast<Guy*>(SCM_CDR (smob));
  guy->mark ();
  return SCM_BOOL_F;
}

scm_sizet
Guy::free_smob (SCM smob)
{
  Guy* guy = reinterpret_cast<Guy*>(SCM_CDR (smob));
  delete guy;
  return (sizeof (Guy));
}

int
Guy::print_smob (SCM smob, SCM port, scm_print_state *pstate)
{
  //Guy* guy = reinterpret_cast<Guy*>(SCM_CDR (smob));
  scm_puts ("<#person:hook>", port);
  return 1;
}

SCM
Guy::get_scm ()
{
  return scm_object;
}

SCM
Guy::scm_set_current (SCM person)
{
  Guy* guy = reinterpret_cast<Guy*>(SCM_CDR (person));

  current_person = guy;

  std::cout << "Current guy: " << current_person << std::endl;

  return SCM_UNSPECIFIED;
}

SCM
Guy::scm_set_scenario (SCM person, SCM smob)
{
  Scenario* s = reinterpret_cast<ScenarioSmobStruct*>(SCM_CDR (smob))->scenario;
  Guy* g = reinterpret_cast<Guy*>(SCM_CDR (person));

  std::cout << "Guy: Setting scenario: g:" << g
	    << " s:" << s << " scenario:" << g->scenario << std::endl;

  if (g->scenario)
    g->scenario->remove (static_cast<AdventObj*>(g));

  g->scenario = s;
  g->scenario->add (g);

  return SCM_UNSPECIFIED;
}

SCM
Guy::call (std::string func)
{
  if (SCM_BOOL_F == scm_object)
    {
      puts ("Guy: don't have scm object for call");
      return SCM_BOOL_F;
    }
  else
    {
      SCM ret_val = gh_call1 (gh_lookup (func.c_str ()), scm_object);
      return ret_val;
    }
}

void
Guy::set_gfx(SCM gfx)
{
  std::string north = SCM_CHARS((gh_call1(gh_lookup ("north"), gfx)));
  std::string south = SCM_CHARS((gh_call1(gh_lookup ("south"), gfx)));
  std::string west  = SCM_CHARS((gh_call1(gh_lookup ("west"),  gfx)));
  std::string east  = SCM_CHARS((gh_call1(gh_lookup ("east"),  gfx)));

  /*std::cout << "Got surfaces: "
    << "  " << north
    << "  " << south
    << "  " << west
    << "  " << east << std::endl; */

  try {
    sur_front = CL_Surface (south.c_str (), app.get_resource ());
    sur_back  = CL_Surface (north.c_str (),  app.get_resource ());
    sur_left  = CL_Surface (west.c_str (),  app.get_resource ());
    sur_right = CL_Surface (east.c_str (), app.get_resource ());
  } catch (CL_Error e) {
    std::cout << "CL_Error: " << e.message << std::endl;
  }
}

SCM
Guy::scm_set_gfx (SCM person, SCM gfx)
{
  Guy* guy = reinterpret_cast<Guy*>(SCM_CDR (person));
  guy->set_gfx (gfx);
  return SCM_UNSPECIFIED;
}

/* EOF */
