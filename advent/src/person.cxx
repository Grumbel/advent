//  $Id: person.cxx,v 1.32 2004/01/14 02:28:24 grumbel Exp $
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

#include <libguile.h>

#include "scm_converter.hxx"
#include "delayed_adv_hook.hxx"
#include "scenario.hxx"
#include "person.hxx"
#include "colmap.hxx"
#include "util.hxx"

namespace Advent {

Person::Person (SCM bind)
  : AdvObj (bind), pos (320, 400, 100), catchable (false), speed (2.0f)
{
  target = pos;
}

Person::~Person ()
{
}

void
Person::update (float delta)
{
  gfx.get()->update (delta);

  //std::cout << "Person:update" << std::endl;
  // update animation
  if (target != pos)
    {
      if (on_target ()) // Person reached the target
	{
	  target = pos;
	  call_hook ();
	}
      else
	{
	  CL_Vector tmp_pos = pos + (direction*delta*20.0);
	  if (scenario->get_colmap ()->get_depth (int(tmp_pos.x), int(tmp_pos.y)) != 0)
	    {
	      pos = tmp_pos;
	      pos.z = scenario->get_colmap ()->get_depth (int(pos.x), int(pos.y));
	    }
	  else // Person reached unwalkable ground, so stop
	    {
	      target = pos;
	      call_hook ();
	    }
	}
    }
  else
    {
      if (get_z_pos () == 0)
	{
	  std::cout << "Person: stuck at: " << pos.x << " " << pos.y
	    << " " << pos.z << std::endl;
	  pos = target;
	}
    }
}

void
Person::call_hook ()
{
  if (hook.get () != 0)
    {
      // The tmp_hook is necessary 'cause the hook can be overwritten inside the hook-call
      SmobTuple<AdvHook> tmp_hook (hook);
      hook.release ();
      tmp_hook.get ()->call ();
    }
}

SCM
Person::set_target (const CL_Vector& newtarget)
{
  target = newtarget;

  // Update the direction
  direction = target - pos;
  direction.normalize ();

  // Set the speed of the person
  direction *= speed;

  hook.set_scm (AdvHookSmob::create (new DelayedAdvHook()));
  return hook.get_scm ();
}

void
Person::draw (boost::dummy_ptr<View> view)
{
  //std::cout << "DummyPtr: " << view.get () << std::endl;
  gfx.get()->get_sprite (this)->draw (view, pos, get_z_pos ());
}

float
Person::get_z_pos ()
{
  if (scenario.get () && scenario->get_colmap ())
    {
      return scenario->get_colmap ()->get_depth (pos.x, pos.y);
    }
  return 1.0;
}

bool
Person::is_over(int x, int y)
{
  int width  = gfx.get()->get_sprite (this)->get_width ();
  int height = gfx.get()->get_sprite (this)->get_height ();

  if (catchable)
    {
      if (x > pos.x - width/2 && x < pos.x + width/2
	  &&
	  y > pos.y - height && y < pos.y)
	return true;
      else
	return false;
    }
  else
    {
      return false;
    }
}

void
Person::set_direction (float angle)
{
  CL_Vector d (0.0, 1.0);
  direction = d.rotate (angle, CL_Vector (0, 0, 1.0));
}

bool
Person::on_target ()
{
  float delta = 10.0;
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
Person::register_guile_bindings ()
{
  puts ("Person::register_guile_bindings ()");

  gh_c_define_public_gsubr("c:person:set-gfx", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_set_gfx));
  gh_c_define_public_gsubr("c:person:create", 1, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_create));
  gh_c_define_public_gsubr("c:person:set-position", 3, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_set_position));
  gh_c_define_public_gsubr("c:person:set-target", 3, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_set_target));
  gh_c_define_public_gsubr("c:person:set-scenario", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_set_scenario));
  gh_c_define_public_gsubr("c:person:get-scenario", 1, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_get_scenario));
  gh_c_define_public_gsubr("c:person:set-direction", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_set_direction));
  gh_c_define_public_gsubr("c:person:set-catchable", 2, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_set_catchable));
  gh_c_define_public_gsubr("c:person:get-position", 1, 0, 0, reinterpret_cast<scm_t_subr>(&Person::scm_person_get_position));
}
/*
SCM
Person::mark (SCM smob)
{
  if (gc_mark_enabled)
    {
      Person* person = smob_cast<Person>(smob);
      return person->hook.get_scm ();
    }
  else
    {
      return SCM_BOOL_F;
    }
}

size_t
Person::free (SCM smob)
{
  if (gc_free_enabled)
    {
      delete smob_cast<Person>(smob);
      return 0; //sizeof (Person);
    }
  else
    {
      return 0;
    }
}

int
Person::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:Person>", port);
  return 1;
}
*/
SCM
Person::scm_person_create (SCM bind)
{
  Person* person = new Person (bind);
  return DrawableSmob::create (person);
}

SCM
Person::scm_person_set_gfx (SCM scm_person, SCM scm_gfx)
{
  std::cout << "Person::scm_person_set_gfx: Not implemented" << std::endl;
  Person* person = smobbox_cast<Person>(scm_person);
  person->gfx.set_scm (scm_gfx);
  return SCM_UNSPECIFIED;
}

SCM
Person::scm_person_set_scenario (SCM scm_person, SCM scm_scenario)
{
  //std::cout  << "scm_person_set_scenario" << std::endl;
  Person* person = smobbox_cast<Person>(scm_person);
  Scenario* scenario = checked_smob_cast<Scenario>(scm_scenario);

  // Check if the scenario has really changed
  if (scenario != person->get_scenario ())
    {
      if (person->scenario.get ())
	{
	  // Remove the person from the scenario
	  person->scenario->remove_advobj (scm_person);
	}

      person->scenario = scenario;
      person->scenario->add_advobj (scm_person);
    }

  return SCM_UNSPECIFIED;
}

SCM
Person::scm_person_get_scenario (SCM scm_person)
{
  return smobbox_cast<Person>(scm_person)->get_scenario ()->get_scm ();
}

SCM
Person::scm_person_set_position (SCM scm_person, SCM x_pos, SCM y_pos)
{
  Person* person = smobbox_cast<Person>(scm_person);
  person->pos.x = scm_to_double (x_pos);
  person->pos.y = scm_to_double (y_pos);

  person->target = person->pos;

  return SCM_UNSPECIFIED;
}

SCM
Person::scm_person_get_position (SCM scm_person)
{
  Person* person = smobbox_cast<Person>(scm_person);

  return scm_cons (scm_from_double (person->pos.x), scm_from_double (person->pos.y));
}

SCM
Person::scm_person_set_target (SCM scm_person, SCM x_pos, SCM y_pos)
{
  Person* person = smobbox_cast<Person>(scm_person);
  return person->set_target (CL_Vector(scm_to_double (x_pos), scm_to_double (y_pos)));
}

SCM
Person::scm_person_set_direction (SCM scm_person, SCM scm_angle)
{
  Person* person = smobbox_cast<Person>(scm_person);
  person->set_direction (scm_to_double (scm_angle));
  return SCM_UNSPECIFIED;
}

SCM
Person::scm_person_set_catchable (SCM scm_person, SCM scm_catchable)
{
  smobbox_cast<Person>(scm_person)->set_catchable (scm_to_bool (scm_catchable));
  return scm_person;
}

} // namespace Advent

/* EOF */
