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

#include <iostream>
#include <algorithm>
#include <ClanLib/Core/core_iostream.h>
#include "clickable_group.hxx"

namespace Advent {

typedef std::vector<Clickable*> Clickables;
Clickables clickable;

ClickableGroup::ClickableGroup()
{
}

ClickableGroup::~ClickableGroup()
{
}

bool
ClickableGroup::is_inside(CL_Point pos)
{
  for (Clickables::reverse_iterator i = clickables.rbegin(); i != clickables.rend(); ++i)
    {
      if ((*i)->is_inside(pos))
        {
          return true;
        }
    }
  return false;
}

Clickable*
ClickableGroup::find_clickable(CL_Point& pos)
{
  for (Clickables::reverse_iterator i = clickables.rbegin(); i != clickables.rend(); ++i)
    {
      Clickable* c = (*i)->find_clickable(pos);
      if (c)
        return c;
    }
  return 0;
}

void
ClickableGroup::add_clickable(Clickable* clickable)
{
  if (clickable)
    clickables.push_back(clickable);
}

void
ClickableGroup::remove_clickable(Clickable* clickable)
{
  clickables.erase(std::remove(clickables.begin(), clickables.end(), clickable));
}

void
ClickableGroup::print(const std::string& prefix)
{
  std::cout << prefix << "ClickableGroup(" << this << ")" << std::endl;
  for (Clickables::iterator i = clickables.begin(); i != clickables.end(); ++i)
    {
      (*i)->print(prefix + " +- ");
    }
}

} // namespace Advent

/* EOF */
