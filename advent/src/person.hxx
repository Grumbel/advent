//  $Id: person.hxx,v 1.19 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef PERSON_HXX
#define PERSON_HXX

#include <guile/gh.h>
#include <ClanLib/core.h>
#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"
#include "adv_obj.hxx"
#include "adv_hook.hxx"
#include "smob_tuple.hxx"
#include "static_smob_tuple.hxx"
#include "person_gfx.hxx"

namespace Advent {

class Scenario;

/** A class for managing the visible components of a (interactivly
    controlled) person. 

    FIXME: Could need seperation: 
    FIXME:   - InteractivePerson;
    FIXME:   - NPCPerson;
    FIXME:   - ...
    FIXME: the Inventory should probally *not* been placed here, but
    FIXME: instead it should be placed only in the scm_person.
    
 */
class Person : public AdvObj
{
private:
  /** A pointer to the scenario in which the person is currently */
  boost::dummy_ptr<Scenario> scenario; 

  /** Position inside the scenario */
  CL_Vector pos;

  /** The position to which the person is walking, if it is equal to
      'pos' then the person is standing */
  CL_Vector target;
  
  /** The direction to the target */
  CL_Vector direction;

  /* FIXME: We should probally have some kind of state variable here
     FIXME: to trigger pickup, turn-around animations and such */

  /** Each drawable is bound to a condition, so you would have one
      condition for left, one for right, one for up, one for down,
      etc. */
  //std::<condition, DrawablePtr> drawables;
  /** FIXME: Do we need a drawable or a sprite here? */

  /** True if this person can be catched with the mouse, since
      interactive person should normally not catchable, this is off by
      default. */
  bool catchable;

  /** The speed of the person in pixel per second, default is 2 */
  float speed;

  /** Hook which is called once the person has reached its target */
  SmobTuple<AdvHook> hook;
  
public:
  Person (SCM bind);
  virtual ~Person ();

  void  update (float delta);
  void  draw (boost::dummy_ptr<View> view);
  
  Scenario* get_scenario () { return scenario.get (); }
  CL_Vector get_direction () { return direction; }
  CL_Vector get_pos () { return pos; }
  void set_pos (float x, float y) { pos.x = x; pos.y = y; }
  /** angle is in radians */
  void set_direction (float angle);

  bool get_catchable () { return catchable; }
  void set_catchable (bool c) { catchable = c; }

  float get_z_pos ();

  bool is_over(int, int);

  SCM set_target (const CL_Vector& newtarget);
  bool on_target ();

  StaticSmobTuple<PersonGfx> gfx;
  
private:
  void call_hook ();

public:
  static void  register_guile_bindings ();

  static SCM scm_person_create (SCM bind);
  static SCM scm_person_set_gfx (SCM person, SCM gfx);

  static SCM scm_person_set_scenario (SCM person, SCM scenario);
  static SCM scm_person_get_scenario (SCM scm_person);

  static SCM scm_person_set_position (SCM person, SCM x_pos, SCM y_pos);
  static SCM scm_person_get_position (SCM person);

  static SCM scm_person_set_direction (SCM person, SCM scm_angle);
  static SCM scm_person_set_target (SCM person, SCM x_pos, SCM y_pos);
  static SCM scm_person_set_catchable (SCM scm_person, SCM scm_catchable);
};

} // namespace Advent

#endif

/* EOF */
