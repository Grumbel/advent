//  $Id: Guy.hh,v 1.16 2001/07/29 11:05:39 grumbel Exp $
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

#ifndef GUY_HH
#define GUY_HH

#include <ClanLib/core.h>
#include "AdventObj.hh"
#include "AdvHook.hh"
#include "Clickable.hh"
#include "Scenario.hh"

class Guy : public AdventObj,
	    public Clickable
{
private:
  // Reference to the scm representation of this person
  SCM scm_object;

  static Guy* current_person;

  CL_Surface sur_left;
  CL_Surface sur_right;
  CL_Surface sur_front;
  CL_Surface sur_back;

  CL_Surface sur_angry;
  CL_Surface sur_questioning;

  float counter;

  CL_Vector direction;


  CL_Vector pos;
  CL_Vector target;

  SCM target_callback;
  SCM target_hook;
  float delta;

public:

  // The scenario in which the guy is standing
  Scenario* scenario;

  enum { NORMAL, QUESTIONING, ANGRY } emotion;

  Guy (SCM p);
  ~Guy ();

  SCM call (std::string func);
  SCM get_scm ();

  bool on_target ();
  void update (float delta);
  void draw_world (int x_offset = 0, int y_offset = 0);

  // Clickable
  void  walk_to_mouse ();
  float priority () { return 0.5; }
  bool mouse_over (int, int) { return true; }

  Scenario* get_scenario () { return scenario; }
  void set_scenario (Scenario* s) { scenario = s; }

  float  get_x_pos () { return pos.x; }
  float  get_y_pos () { return pos.y; }
  float  get_z_pos () { return pos.z; }
  bool is_at (int x, int y);
  void set_gfx (SCM gfx);

  /** Transform a click on a green region into a click onto the
      nearest non-green region */
  CL_Vector transform_to_walkable (CL_Vector);

  std::string get_name () { return "Mogli"; }

  static Guy* get_current () {
    //std::cout << "Returning current person: " << current_person << std::endl;
    return current_person;
  }

  static void Guy::init_guile ();

  // Guile language bindings
  static SCM scm_set_emotion (SCM num);
  static SCM scm_get_x_pos ();
  static SCM scm_get_y_pos ();
  static SCM scm_get_direction ();
  static SCM scm_set_pos (SCM arg_x_pos, SCM arg_y_pos);
  static SCM scm_set_scenario (SCM person, SCM scenario);

  static SCM scm_set_direction (SCM angle);
  static SCM scm_set_target (SCM arg_x_pos, SCM arg_y_pos, SCM callback);
  static SCM scm_set_current (SCM person);
  static SCM scm_set_gfx (SCM person, SCM gfx);
private:
  static long tag;

  void mark ();
public:
  static SCM make (SCM person);
  static SCM mark_smob (SCM smob);
  static scm_sizet free_smob (SCM smob);
  static int print_smob (SCM smob, SCM port, scm_print_state *pstate);
};

#endif

/* EOF */
