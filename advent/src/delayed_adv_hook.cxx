//  $Id: Delayedadv_hook.cxx,v 1.11 2001/10/27 12:23:26 grumbel Exp $
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

#include "scm_converter.hxx"
#include "delayed_adv_hook.hxx"

#include <libguile.h>

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
  if (scm_is_true(scm_procedure_p(scm)))
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
      scm_call_0 (i->get_scm ());
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
  scm_c_define_gsubr("c:delayed-advhook?", 1, 0, 0, reinterpret_cast<scm_t_subr>(scm_delayed_advhook_p));
  scm_c_define_gsubr("c:delayed-advhook:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(scm_delayed_advhook_create));
}

SCM
DelayedAdvHook::scm_delayed_advhook_p (SCM hook)
{
  return scm_from_bool(smobbox_check<DelayedAdvHook>(hook));
}

/* EOF */
