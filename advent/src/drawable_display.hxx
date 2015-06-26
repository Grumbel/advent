//  $Id: drawable_display.hxx,v 1.10 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef DRAWABLEDISPLAY_HXX
#define DRAWABLEDISPLAY_HXX

#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"

#include <list>
#include "smob_tuple.hxx"
#include "drawable.hxx"

namespace Advent {

/** A special layer-like thing for managing drawable's
    FIXME: The dependencies between this class and Scenario are a
    FIXME: bit unclear
 */
class DrawableDisplay
{
private:
  typedef std::list<SmobTuple<Drawable> > DrawableList;
  DrawableList drawables;

public:
  DrawableDisplay ();

  void add (SCM drawable);
  void remove (SCM drawable);
  void clear ();

  void mark ();

  void  update (float delta);
  void  draw (boost::dummy_ptr<View> view);
};

} // namespace Advent

#endif

/* EOF */
