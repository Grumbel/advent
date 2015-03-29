//  $Id: Instantadv_hook.cxx,v 1.6 2001/10/15 18:13:24 grumbel Exp $
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
#include "instant_adv_hook.hxx"

void
InstantAdvHook::add (SCM scm)
{
  std::cout << "InstantAdvHook: add hook" << std::endl;
  if (gh_procedure_p (scm))
    {
      gh_call0 (scm);
    }
}

void
InstantAdvHook::call ()
{
  std::cout << "InstantAdvHook: call hook" << std::endl;
  // do nothing
}

void
InstantAdvHook::register_guile_bindings ()
{
  //gh_new_procedure1_0 ("c:instant-advhook?", adv_hook_p);
  gh_new_procedure0_0 ("c:instant-advhook:create", &InstantAdvHook::instant_advhook_create);
}

SCM
InstantAdvHook::instant_advhook_create ()
{
  return AdvHookSmob::create (new InstantAdvHook ());
}

/* EOF */
