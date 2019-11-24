//  $Id: adv_hook.hxx,v 1.6 2001/10/15 18:13:24 grumbel Exp $
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

#ifndef ADVHOOK_HH
#define ADVHOOK_HH

#include <libguile.h>
#include <list>
#include <algorithm>

#include "adv_hook_smob.hxx"

/** Interface class */
class AdvHook
{
private:
public:
  AdvHook () {}
  virtual ~AdvHook () {}

  virtual void add (SCM scm) =0;
  virtual void call () =0;

  //////////////////////////
  // SCM Smobifiing stuff //
  //////////////////////////
private:
public:
  static void register_guile_bindings ();
  static SCM call_finish (SCM smob);
  static SCM add_finish (SCM smob, SCM func);

  static AdvHookSmob* cast (SCM);
  static long get_smob_tag () { return AdvHookSmob::get_smob_tag (); }
};

#endif

/* EOF */
