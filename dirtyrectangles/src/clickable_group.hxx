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

#ifndef HEADER_CLICKABLE_GROUP_HXX
#define HEADER_CLICKABLE_GROUP_HXX

#include <vector>
#include "clickable.hxx"

namespace Advent {

/** */
class ClickableGroup : public Clickable
{
private:
  typedef std::vector<Clickable*> Clickables;
  Clickables clickables;
public:
  ClickableGroup();
  virtual ~ClickableGroup();

  bool is_inside(CL_Point);

  void add_clickable(Clickable* );
  void remove_clickable(Clickable* );

  Clickable* find_clickable(CL_Point& pos);
  void print(const std::string& prefix);
};

} // namespace Advent

#endif

/* EOF */
