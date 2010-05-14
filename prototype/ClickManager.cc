//  $Id: ClickManager.cc,v 1.7 2001/07/07 20:00:11 grumbel Exp $
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

#include "ClickManager.hh"

bool ClickManager::input_enabled = true;

static bool prio_sort (Clickable* a, Clickable* b)
{
  return (a->priority () > b->priority ());
}

ClickManager::ClickManager () :
  doubleclick_timeout (-1)
{
  on_button_press_slot   
    = CL_Input::sig_button_press.connect (CL_CreateSlot(this, &ClickManager::on_button_press));
  
  on_button_release_slot 
    = CL_Input::sig_button_release.connect (CL_CreateSlot(this, &ClickManager::on_button_release));
}

Clickable* 
ClickManager::get_active (int x_pos, int y_pos)
{
  for (std::list<Clickable*>::iterator i = clickables.begin ();
       i != clickables.end (); ++i)
    {
      std::cout << "active: " << *i << std::endl;
      if ((*i)->mouse_over (x_pos, y_pos))
	{
	  return *i;
	}
    }
  return NULL;
}

void
ClickManager::on_button_press(CL_InputDevice *device, const CL_Key &key)
{
  if (!input_enabled) return;

  clickables.sort (prio_sort);
  //std::cout << "CLICKMANAGER: press" << std::endl;

  for (std::list<Clickable*>::iterator i = clickables.begin ();
       i != clickables.end (); ++i)
    {
      if ((*i)->mouse_over (key.x, key.y))
	{
	  currently_pressed.push_back (*i);
	  
	  if ((*i)->on_mouse_press (key))
	    return;
	}
    }
}

void
ClickManager::on_button_release(CL_InputDevice *device, const CL_Key &key)
{
  if (!input_enabled) return;

  clickables.sort (prio_sort);
  //  std::cout << "CLICKMANAGER: release" << std::endl;

  for (std::list<Clickable*>::iterator i = clickables.begin ();
       i != clickables.end (); ++i)
    {
      if ((*i)->mouse_over (key.x, key.y)
	  && (*i)->on_mouse_release (key))
	{
	  break;
	}
    }

  doubleclick_timeout = CL_System::get_time ();
  double_key = key;
}

void 
ClickManager::add (Clickable* a)
{
  clickables.push_back (a);

  clickables.sort (prio_sort);

  //std::cout << "After sort: " << clickables.size () << std::endl;
  for (std::list<Clickable*>::iterator i = clickables.begin ();
       i != clickables.end (); ++i)
    {
      //std::cout << "Obj: " << *i << " " << (*i)->priority () << std::endl;
    }
}

void 
ClickManager::keep_alive ()
{
  if (!input_enabled) return;

  if (doubleclick_timeout != -1)
    {
      if (doubleclick_timeout < (int) CL_System::get_time ())
	{
	  for (std::list<Clickable*>::iterator i = currently_pressed.begin ();
	       i != currently_pressed.end (); ++i)
	    {
	      if ((*i)->mouse_over (double_key.x, double_key.y) &&
		  (*i)->on_mouse_click (double_key))
		break;
	    }
      	  currently_pressed.clear ();  
	  doubleclick_timeout = -1;
	}
    }
}

void 
ClickManager::init ()
{
  gh_new_procedure0_0 ("c:input:disable", &ClickManager::disable_input);
  gh_new_procedure0_0 ("c:input:enable", &ClickManager::enable_input);
}

SCM 
ClickManager::disable_input ()
{
  input_enabled = false;
  return SCM_UNSPECIFIED;
}

SCM 
ClickManager::enable_input ()
{
  input_enabled = true;
  return SCM_UNSPECIFIED;
}

/* EOF */
