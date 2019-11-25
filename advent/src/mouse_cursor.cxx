//  $Id: mouse_cursor.cxx,v 1.14 2004/01/14 02:28:24 grumbel Exp $
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

#include "scm_converter.hxx"
#include "mouse_cursor.hxx"
#include "util.hxx"

namespace Advent {

MouseCursor::MouseCursor ()
{
  z_pos = 1000.0f;
}

void
MouseCursor::draw (boost::dummy_ptr<View> view)
{
  if (sprite.get ())
    sprite.get ()->draw (view, CL_Vector (CL_Mouse::get_x (), CL_Mouse::get_y ()));
}

void
MouseCursor::update (float delta)
{
  if (sprite.get ())
    sprite.get ()->update (delta);
}

void
MouseCursor::set_sprite (SCM s)
{
  sprite.set_scm (s);
}

void
MouseCursor::register_guile_bindings ()
{
  puts ("MouseCursor::register_guile_bindings ()");

  gh_c_define_public_gsubr("c:mousecursor:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(&MouseCursor::scm_mousecursor_create));
  gh_c_define_public_gsubr("c:mousecursor:set-sprite", 2, 0, 0, reinterpret_cast<scm_t_subr>(&MouseCursor::scm_mousecursor_set_sprite));
}

SCM
MouseCursor::scm_mousecursor_create ()
{
  return LayerSmob::create (new MouseCursor ());
}

SCM
MouseCursor::scm_mousecursor_set_sprite (SCM scm_cursor, SCM scm_sprite)
{
  MouseCursor* cursor = smobbox_cast<MouseCursor>(scm_cursor);
  cursor->set_sprite (scm_sprite);
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
