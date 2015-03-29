//  $Id: debug.hxx,v 1.1 2001/09/20 20:02:36 grumbel Exp $
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

#ifndef DEBUG_HXX
#define DEBUG_HXX

#include <guile/gh.h>

/** FIXME: the current function names are ugly, should be replaced
    FIXME: with something more usefull */
class Debug
{
private:
  static bool free_enabled_;

public:
  // Disable/Enable the usage of free and delete
  static void set_free_enabled (bool f) { free_enabled_ = f; }
  static bool free_enabled () { return free_enabled_; }

  // guile stuff
  static void register_guile_bindings ();
  static SCM scm_set_memory_free (SCM value);
};

#endif

/* EOF */
