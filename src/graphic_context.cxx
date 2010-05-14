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

#include <ClanLib/Display/display.h>
#include <ClanLib/Display/display_window.h>
#include <ClanLib/Display/graphic_context.h>
#include "graphic_context.hxx"

namespace Advent {

GraphicContext::GraphicContext()
{
  scale = 1.0f;
}

GraphicContext::~GraphicContext()
{
}
  
void
GraphicContext::push_translate_offset(int x, int y)
{
  CL_Display::get_current_window()->get_gc()->push_translate(x, y);
}

void
GraphicContext::pop_translate_offset()
{
  CL_Display::get_current_window()->get_gc()->pop_modelview();
}

} // namespace Advent

/* EOF */
