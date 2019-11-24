//  $Id: Instantadv_hook.cxx,v 1.6 2001/10/15 18:13:24 grumbel Exp $
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
#include "instant_adv_hook.hxx"

void
InstantAdvHook::add (SCM scm)
{
  std::cout << "InstantAdvHook: add hook" << std::endl;
  if (scm_is_true(scm_procedure_p(scm)))
    {
      scm_call_0 (scm);
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
  //scm_c_define_gsubr("c:instant-advhook?", 1, 0, 0, adv_hook_p);
  scm_c_define_gsubr("c:instant-advhook:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(&InstantAdvHook::instant_advhook_create));
}

SCM
InstantAdvHook::instant_advhook_create ()
{
  return AdvHookSmob::create (new InstantAdvHook ());
}

/* EOF */
