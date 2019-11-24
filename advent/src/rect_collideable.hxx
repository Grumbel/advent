//  $Id: Rectcollideable.hxx,v 1.4 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef RECTCOLLIDEABLE_HXX
#define RECTCOLLIDEABLE_HXX

#include <libguile.h>
#include <ClanLib/core.h>
#include "collideable.hxx"

namespace Advent {

/** FIXME: Probally useles class, a generic SCM binding class could be
    FIXME: more usefull
 */
class RectCollideable : public Collideable
{
private:
  CL_Rect rect;

public:
  RectCollideable (int x1, int y1,
		   int x2, int y2);

  virtual bool is_over (int x_pos, int y_pos);
  virtual void update (float delta) {}

  // static guile bindings
public:
  static void register_guile_bindings ();

  static SCM scm_rect_collideable_create (SCM x1, SCM y1, SCM x2, SCM y2);
};

} // namespace Advent

#endif

/* EOF */
