//  $Id: Font.cc,v 1.1 2000/12/28 20:00:48 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include "Advent.hh"
#include "Font.hh"

Font font;

CL_Font* Font::operator() (const std::string& fontname)
{
  CL_Font* font = fonts[fontname];
  if (font)
    {
      return font;
    }
  else
    {
      fonts[fontname] = CL_Font::load (fontname.c_str (), app.get_resource ());
      return fonts[fontname];
    }
}


/* EOF */
