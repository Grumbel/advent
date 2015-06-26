//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_VIEW_HXX
#define HEADER_VIEW_HXX

#include <vector>
#include <ClanLib/Core/Math/point.h>
#include <ClanLib/Core/Math/rect.h>
#include <ClanLib/Signals/slot.h>
#include "mark_context.hxx"

class CL_InputEvent;

namespace Advent {

class Drawable;
class Clickable;

/** The View class provides a look at a scene */
class View
{
private:
  MarkContext last_gc;

  Drawable* drawable;
  Clickable* clickable_group;
  Clickable* current_clickable;
  Clickable* mouse_down_clickable;
  Clickable* grab;

  /** the drawable_group offset, used for scrolling */
  CL_Point offset_pos;

  CL_Slot up_slot;
  CL_Slot down_slot;
  CL_Slot move_slot;

  std::vector<CL_Rect> dirty_regions;

  static View* current_;

public:
  static View* current() { return current_; }

  View(Drawable* drawable_group, Clickable* clickable_group);
  ~View();
  
  void set_clickable_group(Clickable* clickable_group);
  void set_drawable (Drawable*  drawable_group);

  void set_pos(CL_Point pos);

  void draw();
  void update(float delta);
  
  void on_mouse_up(const CL_InputEvent& ev);
  void on_mouse_down(const CL_InputEvent& ev);
  void on_mouse_move(const CL_InputEvent& ev);
  
  void grab_input(Clickable* c);
  void release_input();
};

} // namespace Advent

#endif

/* EOF */
