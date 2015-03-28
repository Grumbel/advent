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
#include "sprite_drawable.hxx"

namespace Advent {

// inlined this function for performance reasons.
CL_Pointf calc_hotspot(CL_Origin origin, float hotspot_x, float hotspot_y, float size_width, float size_height)
{
  switch(origin)
    {
    case origin_top_left:
    default:
      return CL_Pointf(-hotspot_x, hotspot_y);
      break;
    case origin_top_center:
      return CL_Pointf(size_width / 2 - hotspot_x, -hotspot_y);
      break;
    case origin_top_right:
      return CL_Pointf(size_width - hotspot_x, -hotspot_y);
      break;
    case origin_center_left:
      return CL_Pointf(-hotspot_x, size_height / 2 - hotspot_y);
      break;
    case origin_center:
      return CL_Pointf(size_width / 2 - hotspot_x, size_height / 2 - hotspot_y);
      break;
    case origin_center_right:
      return CL_Pointf(size_width - hotspot_x, size_height / 2 - hotspot_y);
      break;
    case origin_bottom_left:
      return CL_Pointf(-hotspot_x, size_height - hotspot_y);
      break;
    case origin_bottom_center:
      return CL_Pointf(size_width / 2 - hotspot_x, size_height - hotspot_y);
      break;
    case origin_bottom_right:
      return CL_Pointf(size_width - hotspot_x, size_height - hotspot_y);
      break;
    }
}

SpriteDrawable::SpriteDrawable(const CL_Sprite& arg_sprite,  const CL_Point& arg_pos)
  : sprite(arg_sprite)
{
  set_pos(arg_pos);
}

void
SpriteDrawable::draw(GraphicContext& gc)
{
  sprite.set_scale(gc.get_scale(), gc.get_scale());
  sprite.draw(get_pos().x, get_pos().y);
}

void
SpriteDrawable::draw_marks(MarkContext& gc)
{
  CL_Origin origin;
  int x;
  int y;
  sprite.get_alignment(origin, x, y);

  CL_Pointf p = calc_hotspot(origin, x, y, sprite.get_width(), sprite.get_height());

  gc.mark_region(this, CL_Rect(CL_Point(get_pos().x - (int)p.x,
                                        get_pos().y - (int)p.y), 
                               CL_Size(get_width(), get_height())),
                 sprite.get_current_frame());  
}

void
SpriteDrawable::update(float delta)
{
  sprite.update(delta);
}

} // namespace Advent

/* EOF */
