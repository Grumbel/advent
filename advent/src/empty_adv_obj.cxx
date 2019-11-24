//  $Id: Emptyadv_obj.cxx,v 1.8 2004/01/14 02:28:24 grumbel Exp $
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
#include "empty_adv_obj.hxx"

namespace Advent {

EmptyAdvObj::EmptyAdvObj (SCM b, SCM scm_collideable)
  : AdvObj (b), collideable (scm_collideable)
{
}

bool
EmptyAdvObj::is_over (int x_pos, int y_pos)
{
  return collideable.get ()->is_over (x_pos, y_pos);
}

void
EmptyAdvObj::register_guile_bindings ()
{
  puts ("EmptyAdvObj::register_guile_bindings ()");

  scm_c_define_gsubr("c:empty-advobj:create", 2, 0, 0, reinterpret_cast<scm_t_subr>(&EmptyAdvObj::scm_empty_advobj_create));
}
/*
SCM
EmptyAdvObj::mark (SCM smob)
{
  //FIXME:EmptyAdvObj* empty = smob_cast<EmptyAdvObj>(smob);
  return SCM_BOOL_F;//FIXME:empty->collideable.get_scm ();
}

size_t
EmptyAdvObj::free (SCM smob)
{
  //FIXME:std::cout << "EmptyAdvObj::free" << std::endl;
  //FIXME:delete smob_cast<EmptyAdvObj>(smob);
  return 0; //sizeof (EmptyAdvObj);
}

int
EmptyAdvObj::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:EmptyAdvObj>", port);
  return 1;
}
*/

SCM
EmptyAdvObj::scm_empty_advobj_create (SCM bind, SCM scm_collideable)
{
  return DrawableSmob::create (new EmptyAdvObj(bind, scm_collideable));
}

} // namespace Advent

/* EOF */
