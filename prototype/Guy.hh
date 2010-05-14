//  $Id: Guy.hh,v 1.8 2001/07/01 10:38:16 grumbel Exp $
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

#ifndef GUY_HH
#define GUY_HH

#include <ClanLib/core.h>
#include "AdventObj.hh"
#include "Clickable.hh"

class Guy : public AdventObj,
	    public Clickable
{
private:
  CL_Surface sur_left;
  CL_Surface sur_right;
  CL_Surface sur_front;
  CL_Surface sur_back;

  float counter;

  CL_Vector direction;
  CL_Vector pos;
  CL_Vector target;
  SCM target_callback;
  float delta;

public: 
  Guy ();
  ~Guy ();
  
  bool on_target ();
  void update (float delta);
  void draw_world (int x_offset = 0, int y_offset = 0);

  // Clickable
  bool on_mouse_click(const CL_Key &key);
  float priority () { return 0.5; }
  bool mouse_over (int, int) { return true; }

  float  get_x_pos () { return pos.x; }
  float  get_y_pos () { return pos.y; }
  float  get_z_pos () { return pos.z; }
  bool is_at (int x, int y);
  std::string get_name () { return "Mogli"; }

  static void Guy::init_guile ();

  // Guile language bindings
  static SCM scm_get_x_pos ();
  static SCM scm_get_y_pos ();
  static SCM scm_get_direction ();
  static SCM scm_set_pos (SCM arg_x_pos, SCM arg_y_pos);
  static SCM scm_set_direction (SCM angle);
  static SCM scm_set_target (SCM arg_x_pos, SCM arg_y_pos, SCM callback);
};

extern Guy* the_guy;

#endif

/* EOF */
