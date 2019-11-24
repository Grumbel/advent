//  $Id: key_map_handler.hxx,v 1.4 2003/02/23 17:07:48 grumbel Exp $
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

#ifndef KEYMAPHANDLER_HXX
#define KEYMAPHANDLER_HXX

#include <libguile.h>
#include <ClanLib/display.h>
#include "key_map.hxx"
#include "static_smob_tuple.hxx"

class KeyMapHandler
{
private:
  StaticSmobTuple<KeyMap> keymap;
  CL_Slot on_button_press_slot;
  CL_Slot on_button_release_slot;

public:
  KeyMapHandler ();
  ~KeyMapHandler ();

  void on_button_press (const CL_InputEvent& key);
  void on_button_release (const CL_InputEvent& key);

  // static guile stuff
private:
  static long tag;
public:
  static bool is_a (SCM smob);
  static long get_smob_tag () { return tag; }
  static void register_guile_bindings ();

  static SCM mark (SCM smob);
  static size_t free (SCM smob);
  static int print (SCM image_smob, SCM port, scm_print_state *pstate);

  static SCM scm_keymaphandler_create ();
  static SCM scm_keymaphandler_set_keymap (SCM keymaphandler, SCM keymap);
};

#endif

/* EOF */
