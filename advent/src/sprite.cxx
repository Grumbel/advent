//  $Id: sprite.cxx,v 1.4 2004/01/14 02:28:24 grumbel Exp $
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

#include "rect_sprite.hxx"
#include "surface_sprite.hxx"
#include "scm_converter.hxx"
#include "font_sprite.hxx"

#include "sprite.hxx"

namespace Advent {

SpriteSmob*
Sprite::cast (SCM smob)
{
  return checked_smob_cast<SpriteSmob>(smob);
}

void
Sprite::register_guile_bindings ()
{
  gh_new_procedure1_0 ("c:sprite:get-width", scm_sprite_get_width);
  gh_new_procedure1_0 ("c:sprite:get-height", scm_sprite_get_height);
}

SCM
Sprite::scm_sprite_get_width (SCM scm_sprite)
{
  return gh_int2scm(checked_smob_cast<SpriteSmob>(scm_sprite)->get_child ()->get_width ());
}

SCM
Sprite::scm_sprite_get_height (SCM scm_sprite)
{
  return gh_int2scm(checked_smob_cast<SpriteSmob>(scm_sprite)->get_child ()->get_height ());
}

} // namespace Advent

/* EOF */
