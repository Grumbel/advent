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

#include <map>
#include "resource_manager.hxx"
#include "font_drawable.hxx"

namespace Advent {

typedef std::map<std::string, CL_Font> Fonts;
Fonts fonts;

FontDrawable::FontDrawable(CL_Point pos_, const std::string& font_, const std::string& text_)
  : text(text_)
{
  Fonts::iterator i = fonts.find(font_);
  if (i == fonts.end())
    {
      std::cout << "Loading font" << std::endl;
      font = CL_Font(font_, resources);
      fonts[font_] = font;
      std::cout << "Loading font..done" << std::endl;
    }
  else
    {
      font = i->second;
    }
        
  set_pos(pos_);
}

void
FontDrawable::draw(GraphicContext& gc)
{
  font.draw(get_pos().x, get_pos().y, text);
}

void
FontDrawable::draw_marks(MarkContext& gc)
{
  CL_Rect rect = font.bounding_rect(get_pos().x, get_pos().y, text);
  // FIXME: Calc serial from text
  gc.mark_region(this, rect, 0);
}

} // namespace Advent

/* EOF */
