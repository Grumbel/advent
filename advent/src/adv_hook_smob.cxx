//  $Id: adv_hook_smob.cxx,v 1.1 2001/10/15 07:26:57 grumbel Exp $
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
#include "adv_hook.hxx"
#include "adv_hook_smob.hxx"

long AdvHookSmob::tag;

AdvHookSmob::AdvHookSmob (AdvHook* c)
  : child (c)
{
}

AdvHookSmob::~AdvHookSmob ()
{
  //delete child;
}

void
AdvHookSmob::register_guile_bindings ()
{
  puts ("AdvHookSmob::register_guile_bindings ()");
  tag = scm_make_smob_type ("AdvHookSmob", 0);

  scm_set_smob_mark  (tag, AdvHookSmob::mark);
  scm_set_smob_free  (tag, AdvHookSmob::free);
  scm_set_smob_print (tag, AdvHookSmob::print);
}

SCM
AdvHookSmob::mark (SCM smob)
{
  //FIXME:return unchecked_smob_cast<DrawableSmob>(smob)->sprite.get_scm ();
  return SCM_BOOL_F;
}

size_t
AdvHookSmob::free (SCM smob)
{
  AdvHookSmob* drawable = unchecked_smob_cast<AdvHookSmob>(smob);
  //delete drawable;

  return 0; //sizeof (SpriteDrawable);
}

int
AdvHookSmob::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:AdvHookSmob>", port);
  return 1;
}

SCM
AdvHookSmob::create (AdvHook* obj)
{
  SCM_RETURN_NEWSMOB (tag, new AdvHookSmob (obj));
}

/* EOF */
