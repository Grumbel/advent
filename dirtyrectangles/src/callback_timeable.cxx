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
#include "callback_timeable.hxx"

namespace Advent {

CallbackTimeable::CallbackTimeable(float timeout_)
  : timeout(timeout_),
    done(false)
{
}

CallbackTimeable::~CallbackTimeable()
{
}

void
CallbackTimeable::update(float delta)
{
  if (done)
    return;

  timeout -= delta;
  if (timeout < 0)
    {
      callback();
      done = true;
    }
}

} // namespace Advent

/* EOF */
