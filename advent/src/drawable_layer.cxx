//  $Id: drawable_layer.cxx,v 1.11 2004/01/14 02:28:24 grumbel Exp $
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

#include <stdio.h>

#include "scm_converter.hxx"
#include "drawable_layer.hxx"

namespace Advent {

DrawableLayer::DrawableLayer (SCM d)
  : drawable (d)
{
}

DrawableLayer::~DrawableLayer ()
{
}

void
DrawableLayer::register_guile_bindings ()
{
  puts ("DrawableLayer::register_guile_bindings ()");

  scm_c_define_gsubr("c:drawable-layer:create", 1, 0, 0, reinterpret_cast<scm_t_subr>(&DrawableLayer::scm_drawable_layer_create));
  scm_c_define_gsubr("c:drawable-layer:get-drawable", 1, 0, 0, reinterpret_cast<scm_t_subr>(&DrawableLayer::scm_drawable_layer_get_drawable));
}

SCM
DrawableLayer::scm_drawable_layer_create (SCM scm_drawable)
{
  return LayerSmob::create (new DrawableLayer (scm_drawable));
}

SCM
DrawableLayer::scm_drawable_layer_get_drawable (SCM scm_drawable)
{
  return smobbox_cast<DrawableLayer>(scm_drawable)->drawable.get_scm ();
}

} // namespace Advent

/* EOF */
