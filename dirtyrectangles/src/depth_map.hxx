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

#ifndef HEADER_ADVENT_DEPTH_MAP_HXX
#define HEADER_ADVENT_DEPTH_MAP_HXX

#include <ClanLib/Display/pixel_buffer.h>

class CL_PixelBuffer;
class CL_Point;

namespace Advent {

/** Return the depth of a point, ie map 2d into 3d to provide sprite
    scaling and such. */
class DepthMap
{
private:
  CL_PixelBuffer buffer;
  float scale;
public:
  DepthMap(const std::string name, float scale = 1.0f);
  ~DepthMap();
  
  float get_scale(CL_Point pos);
};

} // namespace Advent

#endif

/* EOF */
