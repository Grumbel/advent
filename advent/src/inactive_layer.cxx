//  $Id: inactive_layer.cxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include "inactive_layer.hxx"

namespace Advent {

InactiveLayer::InactiveLayer (SCM layer)
  : child (layer)
{
}

InactiveLayer::~InactiveLayer ()
{
}

void 
InactiveLayer::update (float delta)
{
}

void 
InactiveLayer::draw (boost::dummy_ptr<View> view)
{
  child.get ()->draw (view);
}
 
bool 
InactiveLayer::is_over (int x_pos, int y_pos)
{
  return false;
}

void 
InactiveLayer::on_button_press (const CL_InputEvent&)
{
}

void 
InactiveLayer::on_button_release (const CL_InputEvent&)
{
}

} // namespace Advent

/* EOF */
