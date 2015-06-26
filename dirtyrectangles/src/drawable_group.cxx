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
#include <algorithm>
#include "drawable_group.hxx"

namespace Advent {

DrawableGroup::DrawableGroup()
{
}

void
DrawableGroup::draw(GraphicContext& gc)
{
  //std::cout << "DrawableGroup::draw(): " << drawables.size() << std::endl;

  for (Drawables::iterator i = drawables.begin(); i != drawables.end(); ++i)
    {
      (*i)->draw(gc);
    }
}

void
DrawableGroup::draw_marks(MarkContext& gc)
{
  for (Drawables::iterator i = drawables.begin(); i != drawables.end(); ++i)
    {
      (*i)->draw_marks(gc);
    }
}

void
DrawableGroup::update(float delta)
{
  for (Drawables::iterator i = drawables.begin(); i != drawables.end(); ++i)
    {
      (*i)->update(delta);
    }
}

void
DrawableGroup::clear()
{
  drawables.clear();
}

void
DrawableGroup::add_drawable(Drawable* drawable)
{
  drawables.push_back(drawable);
}

void
DrawableGroup::remove_drawable(Drawable* drawable)
{
  Drawables::iterator i = std::remove(drawables.begin(), drawables.end(), drawable);
  if (i != drawables.end())
    drawables.erase(i);
}

} // namespace Advent

/* EOF */
