//  $Id: key_map.cxx,v 1.10 2003/02/23 17:07:48 grumbel Exp $
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
#include "key_map.hxx"

long KeyMap::tag;

KeyMap::KeyMap ()
{
}

KeyMap::~KeyMap ()
{
}

void
KeyMap::bind_key (int key, SCM func)
{
  Guile::protect_object (func);

  KeyMapMap::iterator i = keybindings.find (key);

  if (i == keybindings.end ())
    {
      keybindings[key].set_scm (func);
    }
  else
    {
      i->second.set_scm(func);
    }
}

SCM
KeyMap::get_binding (int key)
{
  KeyMapMap::iterator i = keybindings.find (key);

  if (i == keybindings.end ())
    {
      return SCM_BOOL_F;
    }
  else
    {
      return i->second.get_scm ();
    }
}

bool
KeyMap::is_a (SCM smob)
{
  return (long(SCM_CAR (smob)) == get_smob_tag ());
}

void
KeyMap::register_guile_bindings ()
{
  puts ("KeyMap::register_guile_bindings ()");
  tag = scm_make_smob_type ("KeyMap", 0);

  scm_set_smob_mark  (tag, KeyMap::mark);
  scm_set_smob_free  (tag, KeyMap::free);
  scm_set_smob_print (tag, KeyMap::print);

  scm_c_define_gsubr("c:keymap:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(&KeyMap::scm_keymap_create));
  scm_c_define_gsubr("c:keymap:create1", 1, 0, 0, reinterpret_cast<scm_t_subr>(&KeyMap::scm_keymap_create));
  scm_c_define_gsubr("c:keymap:bind-key", 3, 0, 0,  reinterpret_cast<scm_t_subr>(&KeyMap::scm_bind_key));
}

SCM
KeyMap::mark (SCM smob)
{
  /* FIXME: this is causing a crash, don't know why */
  KeyMap* obj = unchecked_smob_cast<KeyMap>(smob);

  for (KeyMapMap::iterator i = obj->keybindings.begin (); i != obj->keybindings.end (); ++i)
    {
      scm_gc_mark (i->second.get_scm ());
    }
  return SCM_BOOL_F;
}

size_t
KeyMap::free (SCM smob)
{
  delete unchecked_smob_cast<KeyMap>(smob);
  return 0; //sizeof (KeyMap);
}

int
KeyMap::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:KeyMap>", port);
  return 1;
}

SCM
KeyMap::scm_keymap_create ()
{
  SCM_RETURN_NEWSMOB (tag, new KeyMap ());
}

/** Inherit the basekeymap from another keymap */
SCM
KeyMap::scm_keymap_create1 (SCM keymap)
{
  SCM_RETURN_NEWSMOB (tag, new KeyMap ());
}

SCM
KeyMap::scm_bind_key (SCM scm_keymap, SCM scm_key, SCM scm_func)
{
  KeyMap* keymap = checked_smob_cast<KeyMap>(scm_keymap);
  keymap->bind_key (scm_to_int(scm_key), scm_func);
  return SCM_UNSPECIFIED;
}

/*KeyMap*
KeyMap::cast (SCM smob)
{
  return checked_smob_cast<KeyMap>(smob);
}*/

/* EOF */
