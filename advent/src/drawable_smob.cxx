//  $Id: drawable_smob.cxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
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
#include "drawable.hxx"
#include "drawable_smob.hxx"

namespace Advent {

long DrawableSmob::tag;

DrawableSmob::DrawableSmob (Drawable* obj)
  : drawable (obj)
{
}

DrawableSmob::~DrawableSmob ()
{
  //FIXME: delete drawable;
}

SCM
DrawableSmob::create (Drawable* obj)
{
  SCM_RETURN_NEWSMOB (tag, new DrawableSmob(obj));
}

void
DrawableSmob::register_guile_bindings ()
{
  puts ("DrawableSmob::register_guile_bindings ()");
  tag = scm_make_smob_type ("DrawableSmob", 0);

  scm_set_smob_mark  (tag, DrawableSmob::mark);
  scm_set_smob_free  (tag, DrawableSmob::free);
  scm_set_smob_print (tag, DrawableSmob::print);
}

SCM
DrawableSmob::mark (SCM smob)
{
  //FIXME:return unchecked_smob_cast<DrawableSmob>(smob)->sprite.get_scm ();
  return SCM_BOOL_F;
}

size_t
DrawableSmob::free (SCM smob)
{
  // FIXME: Memory leak
  //DrawableSmob* drawable = unchecked_smob_cast<DrawableSmob>(smob);
  //  delete drawable;

  return 0; //sizeof (SpriteDrawable);
}

int
DrawableSmob::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:DrawableSmob>", port);
  return 1;
}

} // namespace Advent

/* EOF */
