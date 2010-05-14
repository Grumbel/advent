//  $Id: layer.cxx,v 1.4 2004/01/14 02:28:24 grumbel Exp $
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

#include "drawable_layer.hxx"
#include "button_layer.hxx"
#include "mouse_cursor.hxx"
#include "time_manager.hxx"
#include "scenario_layer.hxx"
#include "coin_layer.hxx"
#include "layer_screen.hxx"
#include "layer.hxx"

namespace Advent {

Layer::Layer ()
{
  z_pos = 10.0f;
}

float
Layer::get_z_pos ()
{
  return z_pos;
}

LayerSmob* 
Layer::cast(SCM smob)
{
  return checked_smob_cast<LayerSmob>(smob);
}

} // namespace Advent

/* EOF */
