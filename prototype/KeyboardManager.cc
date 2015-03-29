//  $Id: KeyboardManager.cc,v 1.2 2001/07/14 21:43:26 grumbel Exp $
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

#include "KeyboardManager.hh"

std::map<int, SCM> KeyboardManager::bindings;
CL_Slot KeyboardManager::slot;

void
KeyboardManager::init ()
{
  slot = CL_Input::sig_button_press.connect (CL_CreateSlot(&KeyboardManager::on_button_press));
  gh_new_procedure2_0 ("adv:bind-key", &KeyboardManager::bind_key);
}

void
KeyboardManager::deinit ()
{
  CL_Input::sig_button_press.disconnect (slot);
}

void
KeyboardManager::bind_key (int key_id, SCM lambda)
{
  bindings[key_id] = lambda;
}

void
KeyboardManager::unbind_key (int key_id)
{
  bindings[key_id] = SCM_BOOL_F;
}

void
KeyboardManager::on_button_press (CL_InputDevice* device , const CL_Key& key)
{
  if (device == CL_Input::keyboards[0])
    {
      std::cout << "Got Button Press: " << key.id << std::endl;

      std::map<int, SCM>::iterator i = bindings.find (key.id);
      if (i != bindings.end ())
	{
	  gh_call0 (i->second);
	}
    }
}

SCM
KeyboardManager::bind_key (SCM key_id, SCM lambda)
{
  if (SCM_INUMP(key_id))
    {
      scm_protect_object (lambda);
      bindings[SCM_INUM (key_id)] = lambda;
    }
  else
    puts ("KeyboardManager: Wrong argument type");

  return SCM_UNSPECIFIED;
}

/* EOF */
