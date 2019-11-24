//  $Id: Polygoncollideable.cxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
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

#include <assert.h>
#include "polygon_collideable.hxx"

namespace Advent {

PolygonCollideable::PolygonCollideable (const std::vector<CL_Vector>& points)
{
  assert (points.size () >= 3);

  CL_Vector last = *(points.end () - 1);

  bounding_box.left   = (int) last.x;
  bounding_box.top    = (int) last.y;
  bounding_box.right  = (int) last.x;
  bounding_box.bottom = (int) last.y;

  for (std::vector<CL_Vector>::const_iterator i = points.begin ();
       i != points.end (); ++i)
    {
      lines.push_back(Line(last, *i));
      last = *i;

      if (i->x < bounding_box.left)
	bounding_box.left = int(i->x);
      if (i->x > bounding_box.right)
	bounding_box.right = int(i->x);
      if (i->y < bounding_box.top)
	bounding_box.top = int(i->y);
      if (i->y > bounding_box.bottom)
	bounding_box.bottom = int(i->y);
    }

  std::cout << "Bounding Box: "
	    << bounding_box.left << " "
	    << bounding_box.top << " "
	    << bounding_box.right << " "
	    << bounding_box.bottom
	    << std::endl;
}

bool
PolygonCollideable::is_over (int x_pos, int y_pos)
{
  if (bounding_box.is_inside (CL_Point(x_pos, y_pos)))
    {
      CL_Vector a (x_pos, y_pos);

      // 5 is a savety factor in case the polygon is a rectangle
      CL_Vector b (bounding_box.right + 5, y_pos);

      Line ray (a, b);

      int intersec_counter = 0;

      for (std::vector<Line>::iterator i = lines.begin (); i != lines.end (); ++i)
	{
	  intersec_counter += lines_intersec (*i, ray).is_valid ();
	}

      return (intersec_counter % 2 != 0);
    }
  else
    return false;
}

void
PolygonCollideable::update (float delta)
{
}

Valid<CL_Vector>
PolygonCollideable::lines_intersec (Line arg_a, Line arg_b)
{
  CL_Vector a = arg_a.first;
  CL_Vector b = arg_a.second - arg_a.first;

  CL_Vector c = arg_b.first;
  CL_Vector d = arg_b.second - arg_b.first;

  double lambda;
  double mu;

  // The lines are parallel
  if ((b.y*d.x - b.x*d.y) == 0.0)
    {
      return Valid<CL_Vector>(CL_Vector (0.0, 0.0), false);
    }

  lambda = (c.y*d.x - c.x*d.y) + (a.x*d.y - a.y*d.x);
  lambda /= (b.y*d.x - b.x*d.y);

  if (d.x != 0.0)
    {
      mu = (a.x + (lambda * b.x) - c.x) / d.x;
    }
  else
    {
      mu = (a.y + (lambda * b.y) - c.y) / d.y;
    }

  CL_Vector col (a + b*lambda);

  if (lambda >= 0 && lambda < 1.0
      && mu >= 0 && mu < 1.0)
    return Valid<CL_Vector>(col, true);
  else
    return Valid<CL_Vector>(col, false);
}

void
PolygonCollideable::register_guile_bindings ()
{
  puts ("PolygonCollideable::register_guile_bindings ()");
  scm_c_define_gsubr("c:polygon-collideable:create", 1, 0, 0,
		       reinterpret_cast<scm_t_subr>(&PolygonCollideable::scm_polygon_collideable_create));
}

SCM
PolygonCollideable::scm_polygon_collideable_create (SCM point_lst)
{
  std::vector<CL_Vector> points;

  while (point_lst != SCM_EOL)
    {
      int x = scm_to_int(scm_car(point_lst));
      point_lst = scm_cdr(point_lst);
      if (point_lst != SCM_EOL)
	{
	  int y = scm_to_int(scm_car(point_lst));
	  point_lst = scm_cdr(point_lst);

	  points.push_back(CL_Vector (x, y));
	}
      else
	{
	  std::cout << "PolygonCollideable: Error: point list length must be a multiple of two" << std::endl;
	}
    }

  return CollideableSmob::create(new PolygonCollideable (points));
}

} // namespace Advent

/* EOF */
