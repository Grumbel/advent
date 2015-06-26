//  $Id: AdvHook.hh,v 1.4 2001/07/10 07:18:17 grumbel Exp $
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

#include <iostream>
#include <guile/gh.h>
#include <list>
#include <algorithm>

class AdvHook
{
private:
  std::list<SCM> finish;
  static int hook_count;
public:
  AdvHook () {
    // Uncomment for memory leak detection
    // std::cout << "Creating hook: " << ++hook_count << std::endl;
  }
  ~AdvHook () {
    // Uncomment for memory leak detection
    // std::cout << "Destructing hook: " << --hook_count << std::endl;
  }

  void mark ()
  {
    for_each (finish.begin (), finish.end (), scm_gc_mark);
  }

  void add_finish (SCM scm)
  {
    if (gh_procedure_p (scm))
      {
	scm_protect_object (scm);
	finish.push_back (scm);
      }
    else
      {
	std::cout << "Not a lambda function" << std::endl;
      }
  }

  void call_finish ()
  {
    for_each (finish.begin (), finish.end (), gh_call0);
  }

  // end of AdvHook definition

  //////////////////////////
  // SCM Smobifiing stuff //
  //////////////////////////

private:
  /// The uniq id of this object type, only used by the guile internals

  static long tag;

public:
  static SCM make ()
  {
    AdvHook* hook = new AdvHook ();

    SCM_RETURN_NEWSMOB (tag, hook);
  }

  static SCM call_finish (SCM smob)
  {
    AdvHook* hook = reinterpret_cast<AdvHook*>(SCM_CDR (smob));

    hook->call_finish ();

    return SCM_UNSPECIFIED;
  }

  static SCM add_finish (SCM smob, SCM func)
  {
    if (SCM_NIMP (smob) && SCM_CAR (smob) == tag)
      {
    scm_protect_object (func);
    AdvHook* hook = reinterpret_cast<AdvHook*>(SCM_CDR (smob));

    hook->add_finish (func);
      }
    else
      {
	std::cout << "Not a correct hook" << std::endl;
      }
    return SCM_UNSPECIFIED;
  }

  static SCM mark_smob (SCM smob)
  {
    AdvHook* hook = reinterpret_cast<AdvHook*>(SCM_CDR (smob));
    hook->mark ();
    return SCM_BOOL_F;
  }

  static scm_sizet free_smob (SCM smob)
  {
    AdvHook* hook = reinterpret_cast<AdvHook*>(SCM_CDR (smob));
    delete hook;
    return sizeof (AdvHook);
  }

  static int print_smob (SCM smob, SCM port, scm_print_state *pstate)
  {
    scm_puts ("<#adv:hook>", port);
    return 1;
  }

  static SCM adv_hook_p (SCM smob)
  {
    if (SCM_NIMP (smob) && SCM_CAR (smob) == tag)
      return SCM_BOOL_T;
    else
      return SCM_BOOL_F;
  }

  static void init ()
  {
    // FIXME: The destructor will never get called!
    tag = scm_make_smob_type ("AdvHook", // name for error mesg.
			      sizeof (AdvHook));

    // Stuff for the Garbage collector and for printing
    scm_set_smob_mark  (tag, &mark_smob);
    scm_set_smob_free  (tag, &free_smob);
    scm_set_smob_print (tag, &print_smob);

    gh_new_procedure1_0 ("adv:hook?", adv_hook_p);
    gh_new_procedure0_0 ("c:adv:hook:make", make);
    gh_new_procedure2_0 ("c:adv:hook:add-finish", add_finish);
    gh_new_procedure1_0 ("c:adv:hook:call-finish", call_finish);
  }
};

#endif

/* EOF */
