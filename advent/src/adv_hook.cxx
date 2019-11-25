//  $Id: adv_hook.cxx,v 1.7 2001/10/16 08:22:11 grumbel Exp $
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

#include "delayed_adv_hook.hxx"
#include "instant_adv_hook.hxx"

#include "scm_converter.hxx"
#include "adv_hook.hxx"

void
AdvHook::register_guile_bindings ()
{
  scm_c_define_gsubr("c:advhook:call", 1, 0, 0, reinterpret_cast<scm_t_subr>(&AdvHook::call_finish));
  scm_c_define_gsubr("c:advhook:add", 2, 0, 0, reinterpret_cast<scm_t_subr>(&AdvHook::add_finish));
}

SCM
AdvHook::call_finish (SCM scm_hook)
{
  // FIXME: wrong cast
  AdvHook* hook = smobbox_cast<AdvHook>(scm_hook);
  hook->call ();
  return SCM_UNSPECIFIED;
}

SCM
AdvHook::add_finish (SCM scm_hook, SCM scm_func)
{
  // FIXME: wrong cast
  AdvHook* hook = smobbox_cast<AdvHook>(scm_hook);
  hook->add (scm_func);
  //std::cout << "AdvHook: adding hook" << std::endl;
  return SCM_UNSPECIFIED;
}

AdvHookSmob*
AdvHook::cast (SCM smob)
{
  return checked_smob_cast<AdvHookSmob>(smob);
}

/* EOF */
