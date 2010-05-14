//  $Id: Surfacecolmap.hxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SURFACECOLMAP_HXX
#define SURFACECOLMAP_HXX

#include <guile/gh.h>
#include <string>
#include <ClanLib/display.h>

#include "colmap.hxx"

namespace Advent {

/** A special type of ColMap which uses a png image to determinate the
    z-pos and the collision 
    (non-walkable = index 0, grey = index 1-255)
*/
class SurfaceColMap : public ColMap
{
private:
  CL_PixelBuffer provider;  
  double scale;
public:
  SurfaceColMap (const std::string&);
  virtual ~SurfaceColMap ();
  
  /** @return depth or 0 if not walkable */
  float get_depth (float x_pos, float y_pos);

  // static guile members
public:
  static void register_guile_bindings ();

  static SCM scm_surfacecolmap_create (SCM filename);
  static SCM scm_surfacecolmap_set_scale (SCM scm_colmap, SCM scm_scale);
  static SCM scm_surfacecolmap_get_scale (SCM scm_colmap);
};

} // namespace Advent

#endif

/* EOF */
