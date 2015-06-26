//  $Id: rect_sprite.hxx,v 1.4 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef RECTSPRITE_HXX
#define RECTSPRITE_HXX

#include <guile/gh.h>
#include "color.hxx"
#include "sprite.hxx"

namespace Advent {

class RectSprite : public Sprite
{
private:
  int   width;
  int   height;
  bool  filled;
  Color color;
public:
  RectSprite (int arg_width, int arg_height, const Color& c);
  virtual ~RectSprite ();

  void update (float delta);
  void draw (boost::dummy_ptr<View> view, const CL_Vector& pos);

  int get_width () const;
  int get_height () const;

  // static guile bindings
public:
  static void register_guile_bindings ();

  static SCM scm_rect_sprite_create (SCM width, SCM height, SCM scm_color);
  static SCM scm_rect_sprite_set_color (SCM scm_rect, SCM scm_color);
};

} // namespace Advent

#endif

/* EOF */
