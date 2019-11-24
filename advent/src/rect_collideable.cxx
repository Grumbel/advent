//  $Id: Rectcollideable.cxx,v 1.10 2004/01/14 02:28:24 grumbel Exp $
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

#include "scm_converter.hxx"
#include "rect_collideable.hxx"

namespace Advent {

RectCollideable::RectCollideable (int x1, int y1,
				  int x2, int y2)
  : rect (x1, y1, x2, y2)
{
}

bool
RectCollideable::is_over (int x_pos, int y_pos)
{
  return rect.is_inside (CL_Point(x_pos, y_pos));
}

void
RectCollideable::register_guile_bindings ()
{
  puts ("RectCollideable::register_guile_bindings ()");
  scm_c_define_gsubr("c:rect-collideable:create", 4, 0, 0, reinterpret_cast<scm_t_subr>(&RectCollideable::scm_rect_collideable_create));
}

/*int
RectCollideable::print (SCM smob, SCM port, scm_print_state *pstate)
{
  RectCollideable* obj = checked_smob_cast<RectCollideable>(smob);
  char str[128];
  snprintf (str, 128, "#<c:RectCollideable: %d:%d-%d:%d>",
	     obj->rect.x1, obj->rect.y1, obj->rect.x2, obj->rect.y2);
  scm_puts (str, port);
  return 1;
}*/

SCM
RectCollideable::scm_rect_collideable_create (SCM x1, SCM y1, SCM x2, SCM y2)
{
  return CollideableSmob::create(new RectCollideable (scm_to_int (x1),
						      scm_to_int (y1),
						      scm_to_int (x2),
						      scm_to_int (y2)));
}

} // namespace Advent

/* EOF */
