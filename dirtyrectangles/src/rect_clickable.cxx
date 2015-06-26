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
#include "rect_clickable.hxx"

namespace Advent {

RectClickable::RectClickable(CL_Rect arg_rect)
{
  rect = arg_rect;
}

bool
RectClickable::is_inside(CL_Point pos)
{
  return rect.is_inside(pos);
}

void
RectClickable::print(const std::string& prefix)
{
  std::cout << prefix << "RectClickable" << std::endl;
}

} // namespace Advent

/* EOF */
