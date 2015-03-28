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

#ifndef HEADER_GRAPHIC_CONTEXT_HXX
#define HEADER_GRAPHIC_CONTEXT_HXX

#include <vector>
#include <ClanLib/Core/Math/rect.h>

namespace Advent {

class Drawable;

/** */
class GraphicContext
{
private:
  float scale;
public:
  GraphicContext();
  ~GraphicContext();
 
  void  set_scale(float s) { scale = s; }
  float get_scale() { return scale; }

  void push_translate_offset(int x, int y);
  void pop_translate_offset();
};

} // namespace Advent

#endif

/* EOF */
