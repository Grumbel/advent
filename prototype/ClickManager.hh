//  $Id: ClickManager.hh,v 1.4 2001/03/28 21:59:57 grumbel Exp $
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

#ifndef CLICKMANAGER_HH
#define CLICKMANAGER_HH

#include <list>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "Clickable.hh"

class ClickManager : public CL_KeepAlive
{
private:
  std::list<Clickable*> clickables;
  CL_Slot on_button_press_slot;
  CL_Slot on_button_release_slot;
  std::list<Clickable*> currently_pressed;

  CL_Key double_key;
  int doubleclick_timeout;

public:
  ClickManager ();
  ~ClickManager () {}

  void add (Clickable* a);
  
  void on_button_press(CL_InputDevice *device, const CL_Key &key);
  void on_button_release(CL_InputDevice *device, const CL_Key &key);

  void keep_alive ();

private:
  Clickable* get_active (int x_pos, int y_pos);
};

#endif

/* EOF */
