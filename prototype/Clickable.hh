//  $Id: Clickable.hh,v 1.3 2001/03/28 21:59:57 grumbel Exp $
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

#ifndef CLICKABLE_HH
#define CLICKABLE_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class Clickable
{
public:
  /// @return true if the click got catched, false if the click was not used
  virtual bool  on_mouse_press (const CL_Key&) { return false; }

  /// @return true if the click got catched, false if the click was not used
  virtual bool  on_mouse_click (const CL_Key&) { return false; }

  /// @return true if the click got catched, false if the click was not used
  virtual bool  on_mouse_release (const CL_Key&) { return false; }

  virtual float priority () =0;
  virtual bool  mouse_over (int, int) =0;
};

#endif

/* EOF */
