//  $Id: Coin.hh,v 1.3 2000/12/30 13:11:56 grumbel Exp $
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

#ifndef COIN_HH
#define COIN_HH

#include <ClanLib/core.h>
#include "Scenario.hh"
class Coin
{
private:
  thSlot on_button_press_slot;
  thSlot on_button_release_slot;
  CL_Surface sur;
  CL_Surface q_mark;
  bool visible;
  int x_pos, y_pos;
  AdventObj* marked_obj;
  
public:
  Coin ();
  ~Coin () {}

  void draw ();
  void update ();
  void on_button_press (CL_InputDevice *device, const CL_Key &key);
  void on_button_release (CL_InputDevice *device, const CL_Key &key);
};

#endif

/* EOF */
