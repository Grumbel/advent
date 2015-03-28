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

#ifndef HEADER_SPRITE_DRAWABLE_HXX
#define HEADER_SPRITE_DRAWABLE_HXX

#include <ClanLib/Display/sprite.h>
#include "drawable.hxx"

namespace Advent {

/** */
class SpriteDrawable : public Drawable
{
private:
  CL_Sprite sprite;
public:
  SpriteDrawable(const CL_Sprite& sprite,  const CL_Point& pos);
  virtual ~SpriteDrawable() {}

  int get_width()  const { return sprite.get_width(); }
  int get_height() const { return sprite.get_height(); }

  void draw(GraphicContext& gc);
  void draw_marks(MarkContext& gc);
  void update(float delta);
};

} // namespace Advent

#endif

/* EOF */
