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

#ifndef HEADER_RECT_OPTIMIZIER_HXX
#define HEADER_RECT_OPTIMIZIER_HXX

#include <vector>
#include <ClanLib/Core/Math/rect.h>

/** */
class RectOptimizier
{
private:
  CL_Rect clip_rect;
  typedef std::vector<CL_Rect> Rects;
  Rects rects;
public:
  RectOptimizier(const CL_Rect& r);
  void add(CL_Rect rect);
  std::vector<CL_Rect> get_rects();
};

#endif

/* EOF */
