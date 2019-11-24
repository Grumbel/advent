//  $Id: mouse_cursor.hxx,v 1.8 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef MOUSECURSOR_HXX
#define MOUSECURSOR_HXX

#include <libguile.h>
#include "sprite.hxx"
#include "smob_tuple.hxx"
#include "layer.hxx"

namespace Advent {

/** A Mouse Cursor layer */
class MouseCursor : public Layer
{
private:
  SmobTuple<Sprite> sprite;

public:
  MouseCursor ();
  virtual ~MouseCursor () {}

  void draw (boost::dummy_ptr<View> view);
  void update (float delta);

  // FIXME: Useless here, drawable's and layers should probally be
  // FIXME: merged
  bool is_over(int, int) { return false; }
  void on_button_press(const CL_InputEvent&) {}
  void on_button_release(const CL_InputEvent&) {}

  void set_sprite (SCM sprite);

  // static guile bindings
public:
  static void register_guile_bindings ();

  static SCM scm_mousecursor_create ();
  static SCM scm_mousecursor_set_sprite (SCM scm_cursor, SCM scm_sprite);
};

} // namespace Advent

#endif

/* EOF */
