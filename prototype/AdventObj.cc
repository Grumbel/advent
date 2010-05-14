//  $Id: AdventObj.cc,v 1.7 2001/07/12 09:23:16 grumbel Exp $
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

#include <ClanLib/core.h>
#include "Scenario.hh"
#include "Advent.hh"
#include "AdventObj.hh"

SurfaceAdvObj::SurfaceAdvObj (Scenario* s, const CL_Surface& arg_sur, const CL_Vector& arg_pos)
  : AdventObj (s)
{
  sur = arg_sur;
  pos = arg_pos;
}

void 
SurfaceAdvObj::draw_world (int x_offset = 0, int y_offset = 0)
{
  sur.put_screen (int(pos.x + x_offset), int(pos.y + y_offset));
}

ostream& operator<<(ostream& ostr, AdventObj& obj)
{
  ostr << obj.get_name ();
  return ostr;
}


/* EOF */
