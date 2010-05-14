//  $Id: CollisionMap.cc,v 1.2 2000/12/29 10:08:16 grumbel Exp $
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
#include "CollisionMap.hh"

CollisionMap::CollisionMap (std::string colmap)
{
  provider =  CL_SurfaceProvider::load (colmap.c_str (), app.get_resource ());
  provider->lock ();
}

CollisionMap::~CollisionMap ()
{
  provider->unlock ();
}

int  
CollisionMap::get_pixel (int x, int y)
{
  return provider->get_pixel (x, y);
}

/* EOF */
