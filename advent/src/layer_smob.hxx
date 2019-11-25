//  $Id: layer_smob.hxx,v 1.2 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef LAYERSMOB_HXX
#define LAYERSMOB_HXX

#include <libguile.h>

namespace Advent {

class Layer;

class LayerSmob
{
private:
  Layer* layer;
  static long tag;
public:
  LayerSmob (Layer*);
  ~LayerSmob ();

  Layer* get_child () { return layer; }

  static long get_smob_tag () { return tag; }
  static void register_guile_bindings ();

  static SCM mark (SCM smob);
  static size_t free (SCM smob);
  static int print (SCM image_smob, SCM port, scm_print_state *pstate);

  static SCM create (Layer* obj);
};

} // namespace Advent

#endif

/* EOF */
