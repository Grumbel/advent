//  $Id: layer_group.hxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef LAYERGROUP_HH
#define LAYERGROUP_HH

#include "smob_tuple.hxx"
#include "layer.hxx"

namespace Advent {

/** FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME
    FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME
    FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME FIXME

    This should be merged with LayerScreen!
*/
class LayerGroup : public Layer
{
private:
  typedef std::list<SmobTuple<Layer> > LayerLst;
  LayerLst layers;

public:
  LayerGroup ();
  virtual ~LayerGroup ();

  void add (SmobTuple<Layer>);

  void update (float delta);
  void draw ();
};

} // namespace Advent

#endif

/* EOF */
