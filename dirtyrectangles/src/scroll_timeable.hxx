//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_SCROLL_TIMEABLE_HXX
#define HEADER_SCROLL_TIMEABLE_HXX

#include "drawable.hxx"
#include "timeable.hxx"

namespace Advent {

class DetachableClickable;
class DetachableDrawable;
class PersonTimeable;

/** This class manages scrolling of a DetachableDrawable */
class ScrollTimeable : public Timeable
{
private:
  DetachableDrawable* drawable;
  DetachableClickable* clickable;
  PersonTimeable* person;

  /** The region that is allowed to be scrolled into */
  CL_Rect  region;
  CL_Point offset;
public:
  ScrollTimeable(DetachableDrawable* d, DetachableClickable* c, PersonTimeable* p);
  
  void update(float delta);
};

} // namespace Advent

#endif

/* EOF */
