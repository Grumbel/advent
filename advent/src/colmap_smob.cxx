//  $Id: colmap_smob.cxx,v 1.2 2004/01/14 02:28:24 grumbel Exp $
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

#include <stdio.h>

#include "scm_converter.hxx"
#include "colmap.hxx"
#include "colmap_smob.hxx"

namespace Advent {

long ColMapSmob::tag;

ColMapSmob::ColMapSmob (ColMap* c)
  : child (c)
{
}

ColMapSmob::~ColMapSmob ()
{
  delete child;
}

void
ColMapSmob::register_guile_bindings ()
{
  puts ("ColMapSmob::register_guile_bindings ()");
  tag = scm_make_smob_type ("ColMapSmob", 0);

  scm_set_smob_mark  (tag, ColMapSmob::mark);
  scm_set_smob_free  (tag, ColMapSmob::free);
  scm_set_smob_print (tag, ColMapSmob::print);
}


SCM
ColMapSmob::mark (SCM smob)
{
  //FIXME:return unchecked_smob_cast<DrawableSmob>(smob)->sprite.get_scm ();
  return SCM_BOOL_F;
}

scm_sizet
ColMapSmob::free (SCM smob)
{
  ColMapSmob* drawable = unchecked_smob_cast<ColMapSmob>(smob);
  //delete drawable;

  return 0; //sizeof (SpriteDrawable);
}

int
ColMapSmob::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:ColMapSmob>", port);
  return 1;
}


SCM
ColMapSmob::create (ColMap* obj)
{
  SCM_RETURN_NEWSMOB (tag, new ColMapSmob (obj));
}

} // namespace Advent

/* EOF */
