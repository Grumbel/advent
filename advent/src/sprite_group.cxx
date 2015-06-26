//  $Id: sprite_group.cxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
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

#include "sprite_group.hxx"

namespace Advent {

SpriteGroup::SpriteGroup()
{
}

SpriteGroup::~SpriteGroup()
{
}

void
SpriteGroup::update (float delta)
{
  for (SpriteList::iterator i = sprites.begin (); i != sprites.end (); ++i)
    {
      i->sprite.get ()->update (delta);
    }
}

void
SpriteGroup::draw (boost::dummy_ptr<View> view, const CL_Vector& pos)
{
  for (SpriteList::iterator i = sprites.begin (); i != sprites.end (); ++i)
    {
      CL_Vector tmp_pos(pos);
      i->sprite.get ()->draw (view, tmp_pos + i->offset);
    }
}

int
SpriteGroup::get_width () const
{
  //FIXME:std::cout << "SpriteGroup::get_width () unimplemented" << std::endl;
  int width = 0;
  for (SpriteList::const_iterator i = sprites.begin (); i != sprites.end (); ++i)
    width = std::max (width, const_cast<Sprite*>(i->sprite.get())->get_width());
  return width;
}

int
SpriteGroup::get_height () const
{
  // FIXME:std::cout << "SpriteGroup::get_height () unimplemented" << std::endl;
  int height = 0;
  for (SpriteList::const_iterator i = sprites.begin (); i != sprites.end (); ++i)
    height = std::max (height,  const_cast<Sprite*>(i->sprite.get())->get_height());
  return height;
}

void
SpriteGroup::add_sprite (SCM scm_sprite, int x_offset, int y_offset)
{
  SpriteOffsetTuple tuple;

  tuple.sprite.set_scm (scm_sprite);
  tuple.offset = CL_Vector(x_offset, y_offset);

  sprites.push_back (tuple);
}

void
SpriteGroup::register_guile_bindings ()
{
  std::cout << "SpriteGroup::register_guile_bindings ()" << std::endl;
  gh_new_procedure0_0 ("c:sprite-group:create", &SpriteGroup::scm_sprite_group_create);
  gh_new_procedure4_0 ("c:sprite-group:add", &SpriteGroup::scm_sprite_group_add);
}

SCM
SpriteGroup::scm_sprite_group_create ()
{
  SpriteGroup* sprite = new SpriteGroup ();
  return SpriteSmob::create (sprite);
}

SCM
SpriteGroup::scm_sprite_group_add (SCM scm_spritegroup, SCM scm_sprite, SCM x_offset, SCM y_offset)
{
  smobbox_cast<SpriteGroup>(scm_spritegroup)->add_sprite (scm_sprite,
							  gh_scm2int (x_offset),
							  gh_scm2int (y_offset));
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
