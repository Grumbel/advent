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

#include "person_timeable.hxx"
#include "detachable_drawable.hxx"
#include "detachable_clickable.hxx"
#include "scroll_timeable.hxx"

namespace Advent {

ScrollTimeable::ScrollTimeable(DetachableDrawable* d, 
                               DetachableClickable* c, 
                               PersonTimeable* p)
  : drawable(d),
    clickable(c),
    person(p)
{
  region = CL_Rect(-1024+640, 0,
                   0, 1);
}

void 
ScrollTimeable::update(float delta)
{
  CL_Point new_offset = CL_Point(320, 240) - person->get_pos();
  
  if (new_offset.x < region.left)
    new_offset.x = region.left;
  else if (new_offset.x > region.right)
    new_offset.x = region.right;    

  if (new_offset.y < region.top)
    new_offset.y = region.top;
  else if (new_offset.y > region.bottom)
    new_offset.y = region.bottom;    
  
  if (abs(new_offset.x - offset.x) > 3
      ||
      abs(new_offset.y - offset.y) > 3)
    {
      offset = new_offset;
      drawable->set_offset(offset);
      clickable->set_offset(offset);
    }
}

} // namespace Advent

/* EOF */
