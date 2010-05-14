//  $Id: Guy.cc,v 1.15 2001/07/01 15:13:31 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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
#include "Guy.hh"

Guy* the_guy;

Guy::Guy ()
{
  sur_front = CL_Surface ("mogli_front", app.get_resource ());
  sur_back  = CL_Surface ("mogli_back", app.get_resource ());
  sur_left  = CL_Surface ("mogli_left", app.get_resource ());
  sur_right = CL_Surface ("mogli_right", app.get_resource ());

  counter = 0;
  pos.x = 320;
  pos.y = 400;
  target = pos;
  delta = 4.0;
  target_callback = SCM_BOOL_F;
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
	  if (Scenario::current->get_colmap ()->get_pixel (int(tmp_pos.x), int(tmp_pos.y)) != 0)
	    {
	      pos = tmp_pos;
	      pos.z = Scenario::current->get_colmap ()->get_pixel (int(pos.x), int(pos.y));
	    }
	  else
	    {
	      target = pos;
	    }
	}
    }
  else
    {
      if (target_callback != SCM_BOOL_F)
	{
	  SCM tmp_callback = target_callback;
	 
	  gh_call0 (target_callback);
	  
	  // We need to check that the callback is still the same,
	  // since it could have been changed in the callback
	  if (tmp_callback == target_callback)
	    target_callback = SCM_BOOL_F;
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
  float zoom = Scenario::current->get_colmap ()->get_pixel (pos.x, pos.y) / 255.0;

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
}

bool 
Guy::on_mouse_click(const CL_Key &key)
{
  //std::cout << "Issued walkto event: " << key.id 
  //    << " " << key.x - view.x_offset << "x" << key.y - view.y_offset
  //    << std::endl;

  /*  std::cout << CL_MOUSE_LEFTBUTTON 
	    << " " << CL_MOUSE_RIGHTBUTTON
	    << " " <<  CL_MOUSE_MIDDLEBUTTON << std::endl;
  */

  if (key.id == CL_MOUSE_LEFTBUTTON || key.id == 0)
    {
      AdventObj* obj = Scenario::current->get_object (key.x, key.y);
      GuileAdventObj* guile_obj = dynamic_cast<GuileAdventObj*>(obj);

      if (obj && guile_obj)
	{
	  //std::cout << "Issued walkto event" << std::endl;
	  //std::cout << "Obj: " << obj << " name: " << guile_obj->get_name () << std::endl;

	  if (guile_obj->call ("adv:walk") == SCM_BOOL_F)
	    {
	      // Walk to the given position
	      direction = CL_Vector (key.x - pos.x - view.x_offset, 
				     key.y - pos.y - view.y_offset);
	      direction.normalize ();
	      direction *= 5.0;
	      target = CL_Vector (key.x - view.x_offset,
				  key.y - view.y_offset);
	    }
	}
      else
	{
	  // Walk to the given position
	  direction = CL_Vector (key.x - pos.x - view.x_offset,
				 key.y - pos.y - view.y_offset);
	  direction.normalize ();
	  direction *= 5.0;
	  target = CL_Vector (key.x - view.x_offset, key.y - view.y_offset);
	}
      return true;
    }

  return false;
}

bool 
Guy::is_at (int x, int y)
{
  return false; // FIXME: Mogli mark is disabled

  float zoom = Scenario::current->get_colmap ()->get_pixel (int(pos.x), int(pos.y)) / 255.0;
  
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
}

SCM
Guy::scm_set_pos (SCM arg_x_pos, SCM arg_y_pos)
{
  the_guy->pos.x = SCM_INUM (arg_x_pos);
  the_guy->pos.y = SCM_INUM (arg_y_pos);
  the_guy->target = the_guy->pos;
  return SCM_UNSPECIFIED;
}

SCM 
Guy::scm_set_direction (SCM angle)
{
  switch (SCM_INUM (angle))
    {
    case 0: // up
      the_guy->direction = CL_Vector (0., -5.);
      break;
    case 1: // right
      the_guy->direction = CL_Vector (5., 0.);
      break;
    case 2: // down
      the_guy->direction = CL_Vector (0., 5.);
      break;
    case 3: // left
      the_guy->direction = CL_Vector (-5., 0.);
      break;
    }
  return SCM_UNSPECIFIED;
}

SCM 
Guy::scm_set_target (SCM arg_x_pos, SCM arg_y_pos, SCM callback)
{
  the_guy->direction = CL_Vector (SCM_INUM(arg_x_pos) - the_guy->pos.x,
				  SCM_INUM (arg_y_pos) - the_guy->pos.y);
  the_guy->direction.normalize ();
  the_guy->direction *= 5.0;
  the_guy->target = CL_Vector (SCM_INUM(arg_x_pos), SCM_INUM (arg_y_pos));
  the_guy->target_callback = callback;

  //printf (" Target Pos: %f %f\n", the_guy->target.x, the_guy->target.y);

  return SCM_UNSPECIFIED;
}

SCM
Guy::scm_get_direction ()
{
  int direction = 0;
  if (fabs(the_guy->direction.x) < fabs(the_guy->direction.y))
    {
      if (the_guy->direction.y > 0)
	direction = 2;
      else 
	direction = 0;
    }
  else
    {
      if (the_guy->direction.x > 0)
	direction = 1;
      else 
	direction = 3;
    }

  return SCM_MAKINUM (direction);
}

SCM 
Guy::scm_get_x_pos ()
{
  return SCM_MAKINUM (int(the_guy->pos.x));
}

SCM 
Guy::scm_get_y_pos ()
{
  return SCM_MAKINUM (int(the_guy->pos.y));
}

/* EOF */
