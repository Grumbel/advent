//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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
#include <ClanLib/Core/core_iostream.h>
#include "detachable_drawable.hxx"

namespace Advent {

DetachableDrawable::DetachableDrawable()
{
  drawable = 0;
  offset.x = 0;
  offset.y = 0;
}

void
DetachableDrawable::draw(GraphicContext& gc)
{
  if (drawable)
    {
      gc.push_translate_offset(offset.x, offset.y);
      drawable->draw(gc);
      gc.pop_translate_offset();
    }
}

void
DetachableDrawable::draw_marks(MarkContext& gc)
{
   if (drawable)
    {
      // FIXME: Doesn't work with sprite drawables with offset
      gc.push_translate_offset(offset.x, offset.y);
      gc.mark_region(this, CL_Rect(drawable->get_pos(),
                                   CL_Size(drawable->get_width(),
                                           drawable->get_height())),
                     static_cast<int>(reinterpret_cast<long>(drawable)));
      drawable->draw_marks(gc);
      gc.pop_translate_offset();
    }
}

void
DetachableDrawable::update(float delta)
{
  if (drawable)
    drawable->update(delta);
}

void
DetachableDrawable::set_drawable(Drawable* d)
{
  drawable = d;
}

Drawable*
DetachableDrawable::get_drawable()
{
  return drawable;
}

void
DetachableDrawable::set_pos(CL_Point p)
{
  Drawable::set_pos(p);
  if (drawable)
    drawable->set_pos(p);
}

void
DetachableDrawable::set_offset(CL_Point p)
{
  offset = p;
}

CL_Point 
DetachableDrawable::get_offset()
{
  return offset;
}

} // namespace Advent

/* EOF */
