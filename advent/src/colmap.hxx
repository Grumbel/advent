//  $Id: colmap.hxx,v 1.4 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef COLMAP_HXX
#define COLMAP_HXX

#include <guile/gh.h>

#include "colmap_smob.hxx"

namespace Advent {

/** The collision map of a scenario. It returns the depth (z-pos) of a
    given 2d position. It also checks if a collision has occured and
    if the region is walkable.
*/
class ColMap
{
private:

public:
  /** @return depth or 0 if not walkable. Range goes from (0,1] */
  virtual float get_depth (float x_pos, float y_pos) =0;

  static ColMapSmob* cast (SCM);
};

} // namespace Advent

#endif

/* EOF */
