//  $Id: Background.hh,v 1.4 2001/04/27 20:42:57 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include <ClanLib/core.h>

class Background
{
private:
  CL_Surface sur;
public:
  Background (std::string);
  virtual ~Background ();

  virtual void draw (int x_offset, int y_offset);
  virtual void update (float delta) {}

  virtual int get_width () { return sur.get_width (); }
  virtual int get_height () { return sur.get_height (); }
};

#endif

/* EOF */
