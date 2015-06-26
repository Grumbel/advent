//  $Id: Coin.hh,v 1.10 2001/07/15 18:54:58 grumbel Exp $
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

#ifndef COIN_HH
#define COIN_HH

#include <ClanLib/core.h>
#include "GuileAdventObj.hh"
#include "Scenario.hh"
#include "Clickable.hh"

class Coin : public Clickable
{
private:
  CL_Surface sur;
  CL_Surface highlight;
  CL_Surface disabled_mark;

  CL_Surface q_mark;
  AdventObj* marked_obj;
  // The object which the guy helds in his hands
  AdventObj* current_obj;
  bool ignore_press;

  CL_Vector click_pos;
  AdventObj* click_obj;
  unsigned int click_time;


  enum { USE, PICKUP, SPEAK, LOOK, NONE, REGIONOUT } current_action;

public:
  Coin ();
  virtual ~Coin () {}

  void set_current_obj (AdventObj* obj);

  void draw ();
  void update (float delta);
  bool on_mouse_press (const CL_Key&);
  bool on_mouse_release (const CL_Key&);
  float priority ();
  bool mouse_over (int, int) { return true; }

  void call_current_action ();
};

extern Coin* coin;

#endif

/* EOF */
