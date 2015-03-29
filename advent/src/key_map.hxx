//  $Id: key_map.hxx,v 1.4 2001/10/15 07:26:57 grumbel Exp $
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

#ifndef KEYMAP_HXX
#define KEYMAP_HXX

#include <map>
#include <guile/gh.h>
#include "scm_obj.hxx"
#include "scm_converter.hxx"

class KeyMap
{
private:
  typedef std::map<int, SCMObj> KeyMapMap;
  std::map<int, SCMObj> keybindings;

public:
  KeyMap ();
  ~KeyMap ();

  void bind_key (int key, SCM func);
  SCM  get_binding (int key);

  // static guile stuff
private:
  static long tag;
public:
  static bool is_a (SCM smob);
  static long get_smob_tag () { return tag; }
  static void register_guile_bindings ();

  static SCM mark (SCM smob);
  static scm_sizet free (SCM smob);
  static int print (SCM image_smob, SCM port, scm_print_state *pstate);

  static SCM scm_keymap_create ();

  /** Inherit the basekeymap from another keymap */
  static SCM scm_keymap_create1 (SCM keymap);

  static SCM scm_bind_key (SCM scm_keymap, SCM scm_key, SCM scm_func);

  //static KeyMap* cast (SCM);
};

#endif

/* EOF */
