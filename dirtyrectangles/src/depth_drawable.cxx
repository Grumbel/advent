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
#include "depth_map.hxx"
#include "depth_drawable.hxx"

namespace Advent {

DepthDrawable::DepthDrawable(Drawable* d, DepthMap* m)
  : drawable(d), depthmap(m)
{
  std::cout << "DepthDrawable: " << drawable << " " << depthmap << std::endl;
}

void
DepthDrawable::update(float delta)
{
  drawable->update(delta);
}

void
DepthDrawable::draw(GraphicContext& gc)
{
  //std::cout << gc.get_scale() << std:: endl;
  if (depthmap)
    {
      gc.set_scale(depthmap->get_scale(drawable->get_pos()));
      drawable->draw(gc);
      gc.set_scale(1.0f);
    }
  else
    {
      drawable->draw(gc);
      std::cout << "DepthDrawable: DepthMap is invalid" << std::endl;
    }
}

void
DepthDrawable::draw_marks(MarkContext& gc)
{
  drawable->draw_marks(gc);
}

/** The width of the drawable, -1 means unlimited ie fills the whole
    screen */
int
DepthDrawable::get_width() const
{
  return drawable->get_width();
}
  
/** The height of the drawable, -1 means unlimited ie fills the
    whole screen */
int
DepthDrawable::get_height() const
{
  return drawable->get_height();
}

void     
DepthDrawable::set_pos(CL_Point p) 
{
  drawable->set_pos(p);
}

CL_Point
DepthDrawable::get_pos() const 
{
  return drawable->get_pos(); 
}

float    
DepthDrawable::get_z_pos() const 
{
  return   drawable->get_z_pos();
}

} // namespace Advent

/* EOF */
