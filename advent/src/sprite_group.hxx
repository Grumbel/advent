//  $Id: sprite_group.hxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SPRITEGROUP_HXX
#define SPRITEGROUP_HXX

#include <ClanLib/core.h>
#include "sprite.hxx"
#include "smob_tuple.hxx"

namespace Advent {

struct SpriteOffsetTuple {
  SmobTuple<Sprite> sprite;
  // FIXME: This kind of duplicates the sprite align handling
  CL_Vector offset;
};

class SpriteGroup : public Sprite
{
private:
  typedef std::list<SpriteOffsetTuple> SpriteList;
  SpriteList sprites;
public:
  SpriteGroup();
  virtual ~SpriteGroup();

  void update (float delta);
  void draw (boost::dummy_ptr<View> view, const CL_Vector& pos);

  int get_width () const;
  int get_height () const;

  void add_sprite (SCM scm_sprite, int x_offset, int y_offset);

  // static guile stuff
  static void register_guile_bindings ();
  static SCM scm_sprite_group_create ();
  static SCM scm_sprite_group_add (SCM scm_spritegroup, SCM scm_sprite, SCM x_offset, SCM y_offset);
};

} // namespace Advent

#endif

/* EOF */
