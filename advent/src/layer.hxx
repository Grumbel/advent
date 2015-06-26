//  $Id: layer.hxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef LAYER_HXX
#define LAYER_HXX

#include <ClanLib/display.h>
#include "boost/dummy_ptr.hpp"
#include "boost/smart_ptr.hpp"
#include "view.hxx"

#include "layer_smob.hxx"

namespace Advent {

/** A Layer is an object (probally a gui widget), which gets input on
    a mouse over event and draws itself

    FIXME: How should input handling be done?
*/
class Layer
{
protected:
  float z_pos;

public:
  Layer ();
  virtual void update (float delta) =0;
  virtual void draw (boost::dummy_ptr<View> view) =0;
  virtual bool is_over (int x_pos, int y_pos) =0;
  virtual void on_button_press (const CL_InputEvent& key) =0;
  virtual void on_button_release (const CL_InputEvent& key) =0;

  virtual float get_z_pos ();

  static LayerSmob* cast (SCM);
};

typedef Layer* LayerPtr;

} // namespace Advent

#endif

/* EOF */
