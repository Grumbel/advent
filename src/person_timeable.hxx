//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PERSON_TIMEABLE_HXX
#define HEADER_PERSON_TIMEABLE_HXX

#include <ClanLib/Core/Math/point.h>
#include <ClanLib/signals.h>
#include "drawable.hxx"
#include "timeable.hxx"

namespace Advent {

class DepthMap;

/** */
class PersonTimeable : public Timeable
{
private:
  Drawable* drawable;
  DepthMap* depthmap;
  CL_Point pos;
  CL_Point target;
  bool on_goal;
  CL_Signal_v0 target_callback;
public:
  PersonTimeable(Drawable* drawable, CL_Point pos);
  virtual ~PersonTimeable() {}

  void update(float delta);
  void walk_to(CL_Point pos);
  void set_pos(CL_Point pos);
  CL_Point get_pos();

  void set_depthmap(DepthMap* d);

  CL_Signal_v0& sig_target_callback();
};

} // namespace Advent

#endif

/* EOF */
