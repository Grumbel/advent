//  $Id: Delayedadv_hook.hxx,v 1.6 2001/10/15 07:26:57 grumbel Exp $
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

#ifndef DELAYEDADVHOOK_HH
#define DELAYEDADVHOOK_HH

#include <guile/gh.h>
#include <list>
#include <algorithm>

#include "adv_hook.hxx"
#include "scm_obj.hxx"

/**
 */
class DelayedAdvHook : public AdvHook
{
private:
  std::list<SCMObj> finish;
  static int hook_count;
public:
  DelayedAdvHook ();
  ~DelayedAdvHook ();

  void add (SCM scm);
  void call ();

  //////////////////////////
  // SCM Smobifiing stuff //
  //////////////////////////
public:
  static void register_guile_bindings ();

  static SCM scm_delayed_advhook_create ();
  static SCM scm_delayed_advhook_p (SCM hook);

  //static SCM adv_hook_p (SCM smob);
};

#endif

/* EOF */
