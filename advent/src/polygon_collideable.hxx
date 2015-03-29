//  $Id: Polygoncollideable.hxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef POLYGONCOLLIDEABLE_HXX
#define POLYGONCOLLIDEABLE_HXX

#include <vector>
#include <iostream>
#include <ClanLib/core.h>
#include "collideable.hxx"
#include "valid.hxx"

namespace Advent {

class PolygonCollideable : public Collideable
{
private:
  typedef std::pair<CL_Vector, CL_Vector> Line;
  std::vector<Line> lines;
  /** Bounding box of the polygon */
  CL_Rect bounding_box;

  Valid<CL_Vector> lines_intersec (Line a, Line b);
public:
  PolygonCollideable (const std::vector<CL_Vector>& points);
  virtual ~PolygonCollideable () {}

  bool is_over (int x_pos, int y_pos);
  void update (float delta);

  // static guile bindings
public:
  static void register_guile_bindings ();
  static SCM scm_polygon_collideable_create (SCM point_lst);
};

} // namespace Advent

#endif

/* EOF */
