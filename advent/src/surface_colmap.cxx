//  $Id: Surfacecolmap.cxx,v 1.19 2004/01/14 02:28:24 grumbel Exp $
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

#include <ClanLib/core.h>
#include "scm_converter.hxx"
#include "surface_colmap.hxx"
#include "util.hxx"

namespace Advent {

SurfaceColMap::SurfaceColMap (const std::string& filename)
  : scale (1.0)
{
  try {
    std::cout << "Extension: " << filename.substr (filename.length () - 4) << std::endl;
    provider = CL_PNGProvider (filename.c_str ());
  } catch (const CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
    assert (0);
  }
  provider.lock ();
}

SurfaceColMap::~SurfaceColMap ()
{
  provider.unlock ();
}

float
SurfaceColMap::get_depth (float x_pos, float y_pos)
{
  int x = int(x_pos);
  int y = int(y_pos);

  if (x > 0 && x < provider.get_width () &&
      y > 0 && y < provider.get_height ())
    {
      // FIXME: Lets hope that the format is correct
      unsigned char* buffer = static_cast<unsigned char*>(provider.get_data());
      return buffer[provider.get_width()*y + x]/255.0f / scale;
    }
  else
    {
      return 0;
    }
}

void
SurfaceColMap::register_guile_bindings ()
{
  puts ("SurfaceColMap::register_guile_bindings ()");

  gh_c_define_public_gsubr("c:surfacecolmap:create", 1, 0, 0,
                    reinterpret_cast<scm_t_subr>(&SurfaceColMap::scm_surfacecolmap_create));

  gh_c_define_public_gsubr("c:surfacecolmap:set-scale", 2, 0, 0,
                    reinterpret_cast<scm_t_subr>(&SurfaceColMap::scm_surfacecolmap_set_scale));
  gh_c_define_public_gsubr("c:surfacecolmap:get-scale", 1, 0, 0,
                    reinterpret_cast<scm_t_subr>(&SurfaceColMap::scm_surfacecolmap_get_scale));
}

/*
  SCM
  SurfaceColMap::mark (SCM smob)
  {
  //FIXME:
  return SCM_BOOL_F;
  }

  size_t
  SurfaceColMap::free (SCM smob)
  {
  std::cout << "ColMap: free" << std::endl;
  delete unchecked_smob_cast<ColMap>(smob);
  return 0; //sizeof (SurfaceColMap);
  }

  int
  SurfaceColMap::print (SCM image_smob, SCM port, scm_print_state *pstate)
  {
  scm_puts ("#<c:SurfaceColMap>", port);
  return 1;
  }
*/
SCM
SurfaceColMap::scm_surfacecolmap_create (SCM filename)
{
  assert (scm_is_string (filename));

  SurfaceColMap* colmap;
  try {
    colmap = new SurfaceColMap (scm_to_cxxstring (filename));
  } catch (const CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
    assert (0);
  }

  return ColMapSmob::create (colmap);
}

SCM
SurfaceColMap::scm_surfacecolmap_set_scale (SCM scm_colmap, SCM scm_scale)
{
  smobbox_cast<SurfaceColMap>(scm_colmap)->scale = scm_to_double (scm_scale);
  return SCM_UNSPECIFIED;
}

SCM
SurfaceColMap::scm_surfacecolmap_get_scale (SCM scm_colmap)
{
  return scm_from_double(smobbox_cast<SurfaceColMap>(scm_colmap)->scale);
}

} // namespace Advent

/* EOF */
