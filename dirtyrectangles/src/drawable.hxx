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

#ifndef HEADER_DRAWABLE_HXX
#define HEADER_DRAWABLE_HXX

#include <ClanLib/Core/Math/point.h>
#include "graphic_context.hxx"
#include "mark_context.hxx"

namespace Advent {

/** */
class Drawable
{
private:
  CL_Point pos;
  CL_Point tmp_pos;
  float z_pos;
public:
  Drawable();
  virtual ~Drawable();

  virtual void update(float delta) =0;
  virtual void draw(GraphicContext& gc) =0;
  virtual void draw_marks(MarkContext& gc) =0;

  /** The width of the drawable, -1 means unlimited ie fills the whole
      screen */
  virtual int get_width() const { return -1; }

  /** The height of the drawable, -1 means unlimited ie fills the
      whole screen */
  virtual int get_height() const { return -1; }

  virtual void     set_pos(CL_Point p) { pos = p; }
  virtual CL_Point get_pos() const { return pos; }
  virtual float    get_z_pos() const { return z_pos; }
};

} // namespace Advent

#endif

/* EOF */
