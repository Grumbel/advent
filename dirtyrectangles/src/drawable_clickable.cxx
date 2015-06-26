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

#include <iostream>
#include "drawable_clickable.hxx"

namespace Advent {

DrawableClickable::DrawableClickable(Drawable* d)
  : drawable(d)
{
}

bool
DrawableClickable::is_inside(CL_Point mpos)
{
  CL_Point pos = drawable->get_pos();
  return (pos.x < mpos.x && pos.x + drawable->get_width() > mpos.x
          && pos.y < mpos.y && pos.y + drawable->get_height() > mpos.y);
}

void
DrawableClickable::print(const std::string& prefix)
{
  std::cout << prefix << "DrawableClickable" << std::endl;
}

} // namespace Advent

/* EOF */
