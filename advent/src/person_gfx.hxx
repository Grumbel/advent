//  $Id: person_gfx.hxx,v 1.6 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef PERSONGFX_HXX
#define PERSONGFX_HXX

#include "sprite.hxx"

namespace Advent {

class Person;

// FIXME: Temporary Hack
struct PersonGfxPack
{
  SmobTuple<Sprite> north;
  SmobTuple<Sprite> east;
  SmobTuple<Sprite> south;
  SmobTuple<Sprite> west;

  PersonGfxPack (SCM arg_north, SCM arg_east,
		 SCM arg_south, SCM arg_west)
    : north (arg_north),
      east  (arg_east),
      south (arg_south),
      west  (arg_west)
  {}

  void update (float delta) {
    west.get()->update (delta);
    east.get()->update (delta);
    north.get()->update (delta);
    south.get()->update (delta);
  }
};

class PersonGfx
{
private:
  PersonGfxPack* walking;
  PersonGfxPack* standing;
public:
  PersonGfx (SCM);
  ~PersonGfx ();

  Sprite* get_sprite (Person* person);
  void update (float delta);

  // static guile stuff
private:
  static long tag;
public:
  static SCM mark (SCM smob);
  static scm_sizet free (SCM smob);
  static int print (SCM image_smob, SCM port, scm_print_state *pstate);

  static long get_smob_tag () { return tag; }
  static void register_guile_bindings ();
  static SCM scm_persongfx_create (SCM lst);
};

} // namespace Advent

#endif

/* EOF */
