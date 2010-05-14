//  $Id$
// 
//  Advent
//  Copyright (C) 2003 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_RECT_DRAWABLE_HXX
#define HEADER_RECT_DRAWABLE_HXX

#include <ClanLib/Display/color.h>
#include <ClanLib/Core/Math/rect.h>
#include "drawable.hxx"

namespace Advent {

/** */
class RectDrawable : public Drawable
{
private:
  CL_Rect  rect;
  CL_Color color;
public:
  RectDrawable(const CL_Rect& r, const CL_Color& c);

  void update(float delta);
  void draw(GraphicContext& gc);
  void draw_marks(MarkContext& gc);
};

} // namespace Advent

#endif

/* EOF */
