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
#include "depth_map.hxx"
#include "person_timeable.hxx"

namespace Advent {

PersonTimeable::PersonTimeable(Drawable* drawable_, CL_Point pos_)
  : drawable(drawable_),
    pos(pos_),
    target(pos),
    on_goal(true)
{
  depthmap = 0;
}

void
PersonTimeable::update(float delta)
{
  if (!on_goal)
    {
      CL_Point old_pos = pos;
      bool x_ok = false;
      bool y_ok = false;

      if (pos.x + 5 < target.x)
        pos.x += 5;
      else if (pos.x - 5 > target.x)
        pos.x -= 5;
      else
        x_ok = true;

      if (pos.y + 5 < target.y)
        pos.y += 5;
      else if (pos.y - 5 > target.y)
        pos.y -= 5;
      else
        y_ok = true;

      drawable->set_pos(pos);

      if (x_ok && y_ok)
        {
          // Check here if pos is == target and call 'unreachable' or so if not
          target_callback();
          target_callback = CL_Signal_v0();
          on_goal = true;
        }
      
      if (depthmap)
        {
          if (depthmap->get_scale(pos) == 0.0f)
            {
              std::cout << "Reached boarder of map" << std::endl;
              pos = old_pos;
              target = pos;
              drawable->set_pos(pos);     
            }
        }
    }
}

void
PersonTimeable::walk_to(CL_Point pos_)
{
  target_callback = CL_Signal_v0();
  target = pos_;
  on_goal = false;
}

void
PersonTimeable::set_pos(CL_Point pos_)
{
  target_callback = CL_Signal_v0();
  target = pos = pos_;
  on_goal = true;
  drawable->set_pos(pos);
}

CL_Point
PersonTimeable::get_pos()
{
  return pos;
}

CL_Signal_v0&
PersonTimeable::sig_target_callback()
{
  return target_callback;
}

void
PersonTimeable::set_depthmap(DepthMap* d)
{
  depthmap = d;
}

} // namespace Advent

/* EOF */
