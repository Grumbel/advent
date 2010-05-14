//  $Id: Delayedadv_hook.cxx,v 1.11 2001/10/27 12:23:26 grumbel Exp $
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
#include "delayed_adv_hook.hxx"

/// The uniq id of this object type, only used by the guile internals
int DelayedAdvHook::hook_count;

DelayedAdvHook::DelayedAdvHook () { 
  // Uncomment for memory leak detection
  // std::cout << "Creating hook: " << ++hook_count << std::endl; 
}

DelayedAdvHook::~DelayedAdvHook () { 
  // Uncomment for memory leak detection
  // std::cout << "Destructing hook: " << --hook_count << std::endl; 
}

void 
DelayedAdvHook::add (SCM scm)
{
  //std::cout << "DelayedAdvHook: adding hook" << std::endl;
  if (gh_procedure_p (scm))
    {
      finish.push_back (SCMObj(scm));
    }
  else
    {
      std::cout << "Warrning: DelayedAdvHook::add: Not a lambda function" << std::endl;
    }
}

void 
DelayedAdvHook::call () 
{
  //std::cout << "DelayedAdvHook: calling hook" << std::endl;
  for (std::list<SCMObj>::iterator i = finish.begin ();
       i != finish.end (); ++i)
    {
      gh_call0 (i->get_scm ());
    }
}

SCM 
DelayedAdvHook::scm_delayed_advhook_create ()
{
  return AdvHookSmob::create (new DelayedAdvHook ());
}

void 
DelayedAdvHook::register_guile_bindings () 
{
  gh_new_procedure1_0 ("c:delayed-advhook?", scm_delayed_advhook_p);
  gh_new_procedure0_0 ("c:delayed-advhook:create", scm_delayed_advhook_create);
}

SCM
DelayedAdvHook::scm_delayed_advhook_p (SCM hook)
{
  return gh_bool2scm(smobbox_check<DelayedAdvHook>(hook));
}

/* EOF */
