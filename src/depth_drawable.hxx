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

#ifndef HEADER_DEPTH_DRAWABLE_HXX
#define HEADER_DEPTH_DRAWABLE_HXX

#include "drawable.hxx"

namespace Advent {

class Drawable;
class DepthMap;

/** */
class DepthDrawable : public Drawable
{
private:
  Drawable* drawable;
  DepthMap* depthmap;
public:
  DepthDrawable(Drawable* d, DepthMap* m);

  void update(float delta);
  void draw(GraphicContext& gc);
  void draw_marks(MarkContext& gc);

  /** The width of the drawable, -1 means unlimited ie fills the whole
      screen */
  int get_width() const;
  
  /** The height of the drawable, -1 means unlimited ie fills the
      whole screen */
  int get_height() const;

  void     set_pos(CL_Point p);
  CL_Point get_pos() const;
  float    get_z_pos() const;
};

} // namespace Advent

#endif

/* EOF */
