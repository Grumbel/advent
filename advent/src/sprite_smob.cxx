//  $Id: sprite_smob.cxx,v 1.2 2004/01/14 02:28:24 grumbel Exp $
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

#include <stdio.h>

#include "scm_converter.hxx"
#include "sprite_smob.hxx"

namespace Advent {

long SpriteSmob::tag;

SpriteSmob::SpriteSmob (Sprite* s)
  : sprite (s)
{
}

SpriteSmob::~SpriteSmob ()
{
  // FIXME:
  //delete sprite;
}


void
SpriteSmob::register_guile_bindings ()
{
  puts ("SpriteSmob::register_guile_bindings ()");
  tag = scm_make_smob_type ("SpriteSmob", 0);

  scm_set_smob_mark  (tag, SpriteSmob::mark);
  scm_set_smob_free  (tag, SpriteSmob::free);
  scm_set_smob_print (tag, SpriteSmob::print);
}

SCM 
SpriteSmob::mark (SCM smob)
{
  //FIXME:return unchecked_smob_cast<SpriteSmob>(smob)->sprite.get_scm ();
  return SCM_BOOL_F;
}

scm_sizet
SpriteSmob::free (SCM smob) 
{
  SpriteSmob* sprite_smob = unchecked_smob_cast<SpriteSmob>(smob);
  //delete sprite_smob;
  
  return 0; //sizeof (SpriteDrawable);
}

int 
SpriteSmob::print (SCM image_smob, SCM port, scm_print_state *pstate) 
{
  scm_puts ("#<c:SpriteSmob>", port);
  return 1;
}

SCM
SpriteSmob::create (Sprite* sprite)
{
  SCM_RETURN_NEWSMOB (tag, new SpriteSmob (sprite));
}

} // namespace Advent

/* EOF */
