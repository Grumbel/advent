//  $Id: Spritecollideable.hxx,v 1.5 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SPRITECOLLIDEABLE_HXX
#define SPRITECOLLIDEABLE_HXX

#include <guile/gh.h>
#include "sprite.hxx"
#include "collideable.hxx"

namespace Advent {

/** Collideable for use with a SpriteDrawable, it simply checks if a
    given coordinate is inside the sprite or not.

    FIXME: Checking for the alpha-channel of the sprite should be added.
*/
class SpriteCollideable : public Collideable
{
private:
  SpritePtr sprite;
  CL_Vector pos;

public:
  SpriteCollideable (SpritePtr s, const CL_Vector& p) : sprite (s), pos (p) {}
  virtual ~SpriteCollideable () {}

  bool is_over (int x_pos, int y_pos);
  void update (float delta);

  // static guile stuff
public:
  static void register_guile_bindings ();

  static SCM scm_sprite_collideable_create (SCM sprite_drawable);
};

} // namespace Advent

#endif

/* EOF */
