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

#ifndef HEADER_CLICKABLE_HXX
#define HEADER_CLICKABLE_HXX

#include <ClanLib/Core/Math/point.h>
#include <ClanLib/signals.h>
#include <libguile.h>
#include <guile/gh.h>
#include <string>

namespace Advent {

class ClickableCallback
{
public:
  virtual ~ClickableCallback() {}
  virtual void call(CL_Point pos) =0;
};

template<class Func>
class GenericClickableCallback : public ClickableCallback
{
private:
  Func f;
public:
  GenericClickableCallback(Func f_)
  : f(f_){}

  virtual ~GenericClickableCallback() {}

  void call(CL_Point pos) { f(gh_int2scm(pos.x),
                              gh_int2scm(pos.y)); }
};

/** */
class Clickable
{
private:
  ClickableCallback* callback;

  CL_Signal_v1<CL_Point> mouse_down;
  CL_Signal_v1<CL_Point> mouse_up;

  CL_Signal_v0 mouse_enter;
  CL_Signal_v0 mouse_leave;
public:
  Clickable() { callback = 0;}
  virtual ~Clickable() { delete callback; }

  void set_callback(ClickableCallback* c) { delete callback; callback = c; }
  void call_callback(CL_Point pos) { if (callback) callback->call(pos); }

  CL_Signal_v0& sig_mouse_enter() { return mouse_enter; }
  CL_Signal_v0& sig_mouse_leave() { return mouse_leave; }

  CL_Signal_v1<CL_Point>& sig_mouse_down() { return mouse_down; }
  CL_Signal_v1<CL_Point>& sig_mouse_up() { return mouse_up; }

  virtual Clickable* find_clickable(CL_Point& pos) { 
    if (is_inside(pos)) 
      return this;
    else
      return 0;
  }

  virtual CL_Point screen2world(CL_Point pos) { return pos; }

  virtual bool is_inside(CL_Point pos) =0;
  virtual void print(const std::string& prefix) =0;
};

} // namespace Advent

#endif

/* EOF */
