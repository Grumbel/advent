//  $Id$
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

class Guy : public AdventObj
{
private:
  CL_Surface sur_left;
  CL_Surface sur_right;
  CL_Surface sur_front;
  CL_Surface sur_back;

  int counter;
  thSlot on_button_press_slot;

  CL_Vector direction;
  CL_Vector pos;
  CL_Vector target;
  float delta;

public: 
  Guy ();
  ~Guy ();
  
  bool on_target ();
  void update ();
  void draw_world ();
  void on_button_press(CL_InputDevice *device, const CL_Key &key);
  float  get_z_pos () { return pos.z; }
  bool is_at (int x, int y);
  std::string get_name () { return "Mogli"; }
};

#endif

/* EOF */
