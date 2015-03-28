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

#include <ClanLib/Display/pixel_buffer.h>
#include <ClanLib/Display/Providers/provider_factory.h>
#include <ClanLib/Core/Math/point.h>
#include "resource_manager.hxx"
#include "depth_map.hxx"

namespace Advent {

DepthMap::DepthMap(const std::string name, float s)
  : scale(s)
{
  buffer = CL_ProviderFactory::load("../data/images/" + name + ".png");
}

DepthMap::~DepthMap()
{
}

float
DepthMap::get_scale(CL_Point pos)
{
  buffer.lock();
  unsigned char* buf = static_cast<unsigned char*>(buffer.get_data());
  int depth;
  int i = pos.y * buffer.get_width() + pos.x;

  if (i > 0 && i < buffer.get_height() * int(buffer.get_pitch()))
    depth = buf[i];
  else
    depth = 255;

  buffer.unlock();
  
  return (depth/255.0) * scale;
}

} // namespace Advent

/* EOF */
