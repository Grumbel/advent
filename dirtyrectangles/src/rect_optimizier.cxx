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
#include <ClanLib/Core/core_iostream.h>
#include "rect_optimizier.hxx"

RectOptimizier::RectOptimizier(const CL_Rect& r)
  : clip_rect(r)
{
  
}

void
RectOptimizier::add(CL_Rect r)
{
  // FIXME: insert microtile/uta stuff or something similar to get rid
  // of overlapping redraws
  if (clip_rect.is_overlapped(r))
    {
      r.normalize();
      CL_Rect c = clip_rect.calc_union(r);
      //std::cout << clip_rect << r << "Union: " << c << std::endl;
      rects.push_back(c);
    }
}

std::vector<CL_Rect>
RectOptimizier::get_rects()
{
  return rects;
}

/* EOF */
