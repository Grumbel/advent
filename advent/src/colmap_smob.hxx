//  $Id: colmap_smob.hxx,v 1.2 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef COLMAPSMOB_HXX
#define COLMAPSMOB_HXX

#include <libguile.h>

namespace Advent {

class ColMap;

class ColMapSmob
{
private:
  ColMap* child;
  static long tag;
public:
  ColMapSmob (ColMap*c);
  ~ColMapSmob ();

  ColMap* get_child () { return child; }

  static void register_guile_bindings ();
  static SCM mark (SCM smob);
  static size_t free (SCM smob);
  static int print (SCM image_smob, SCM port, scm_print_state *pstate);

  static long get_smob_tag () { return tag; }
  static SCM  create (ColMap*);
};

} // namespace Advent

#endif

/* EOF */
