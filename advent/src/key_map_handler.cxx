//  $Id: key_map_handler.cxx,v 1.10 2003/02/23 17:07:48 grumbel Exp $
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

#include "scm_converter.hxx"
#include "key_map_handler.hxx"

long KeyMapHandler::tag;

KeyMapHandler::KeyMapHandler ()
{
  puts ("9840898 Input disabled"); // Sun Feb 23 17:35:45 2003
#if 0
  on_button_press_slot   
    = CL_Input::sig_button_press ().connect (this, &KeyMapHandler::on_button_press);
  
  on_button_release_slot 
    = CL_Input::sig_button_release ().connect (this, &KeyMapHandler::on_button_release);
#endif 
}

KeyMapHandler::~KeyMapHandler ()
{
  // FIXME: disconnect here
}

void
KeyMapHandler::on_button_press (const CL_InputEvent&)
{
#if 0 //Sun Feb 23 17:41:09 2003
  if (device == CL_Input::keyboards[0])
    {
      if (keymap.get ())
	{
	  SCM func = keymap.get ()->get_binding (key.id);
	  if (func != SCM_BOOL_F)
	    {
	      gh_call0 (func);
	    }
	}
    }
#endif
}

void 
KeyMapHandler::on_button_release (const CL_InputEvent&)
{
}

bool 
KeyMapHandler::is_a (SCM smob)
{
  return (int(SCM_CAR (smob)) == get_smob_tag ());
}

void 
KeyMapHandler::register_guile_bindings ()
{
  puts ("KeymapHandler::register_guile_bindings ()");
  tag = scm_make_smob_type ("KeymapHandler", 0);

  scm_set_smob_mark  (tag, KeyMapHandler::mark);
  scm_set_smob_free  (tag, KeyMapHandler::free);
  scm_set_smob_print (tag, KeyMapHandler::print);

  gh_new_procedure0_0 ("c:keymaphandler:create", &KeyMapHandler::scm_keymaphandler_create);
  gh_new_procedure2_0 ("c:keymaphandler:set-keymap", scm_keymaphandler_set_keymap);
}

SCM
KeyMapHandler::mark (SCM smob)
{
  /* FIXME: This is causing a crash */
  KeyMapHandler* handler = unchecked_smob_cast<KeyMapHandler>(smob);
  handler->keymap.mark ();
  return SCM_BOOL_F;
}

scm_sizet
KeyMapHandler::free(SCM smob)
{
  delete unchecked_smob_cast<KeyMapHandler>(smob);
  return 0; //sizeof(KeyMapHandler);
}

int
KeyMapHandler::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:KeyMapHandler>", port);
  return 1;
}

SCM 
KeyMapHandler::scm_keymaphandler_create ()
{
  SCM_RETURN_NEWSMOB (tag, new KeyMapHandler ());
}

SCM 
KeyMapHandler::scm_keymaphandler_set_keymap (SCM scm_keymaphandler, SCM scm_keymap)
{
  KeyMapHandler* handler = checked_smob_cast<KeyMapHandler>(scm_keymaphandler);
  handler->keymap.set_scm (scm_keymap);
  return SCM_UNSPECIFIED;
}

/* EOF */
