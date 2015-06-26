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

#include <ClanLib/Display/display.h>
#include <ClanLib/Display/display_window.h>
#include <ClanLib/Display/graphic_context.h>
#include "mark_context.hxx"

namespace Advent {

MarkContext::MarkContext()
{
  
}

MarkContext::~MarkContext()
{
}

std::vector<CL_Rect>
MarkContext::calc_diff(MarkContext& gc)
{
  std::vector<CL_Rect> dirty;

  if (gc.regions.empty())
    {
          dirty.push_back(CL_Rect(0, 0, 640, 480));
      return dirty;
    }
  Regions::iterator i = regions.begin();
  Regions::iterator j = gc.regions.begin();

  while (i != regions.end() && j != gc.regions.end())
    {
      if (i->rect != j->rect
          || i->serial != j->serial)
        {
          CL_Rect rect;

          rect.left  = std::min(i->rect.left, j->rect.left);
          rect.right = std::max(i->rect.right, j->rect.right);

          rect.top    = std::min(i->rect.top, j->rect.top);
          rect.bottom = std::max(i->rect.bottom, j->rect.bottom);

          dirty.push_back(rect);
        }

      ++i;
      ++j;
    }  
  return dirty;
}

void
MarkContext::draw()
{
  for(Regions::iterator i = regions.begin(); i != regions.end(); ++i)
    {
      CL_Display::draw_rect(i->rect, CL_Color(0, 0, 255, 100));
    }
}

void
MarkContext::mark_region(Drawable* drawable, CL_Rect rect, int serial)
{
  // FIXME:
  rect.left  += 0; //CL_Display::get_current_window()->get_gc()->get_translate_x();
  rect.right += 0; //CL_Display::get_current_window()->get_gc()->get_translate_x();

  rect.top    += 0; //CL_Display::get_current_window()->get_gc()->get_translate_y();
  rect.bottom += 0; //CL_Display::get_current_window()->get_gc()->get_translate_y();

  Region region;
  region.drawable = drawable;
  region.serial   = serial;
  region.rect     = rect;
 
  regions.push_back(region);
}
  
void
MarkContext::push_translate_offset(int x, int y)
{
  CL_Display::get_current_window()->get_gc()->push_translate(x, y);
}

void
MarkContext::pop_translate_offset()
{
  CL_Display::get_current_window()->get_gc()->pop_modelview();
}

} // namespace Advent

/* EOF */
