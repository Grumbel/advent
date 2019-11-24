//  $Id: display.cxx,v 1.5 2004/01/14 02:28:24 grumbel Exp $
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

//#include <config.h>
#include <iostream>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include "display.hxx"

namespace Advent {

void
Display::register_guile_bindings ()
{
  scm_c_define_gsubr("c:display:setup", 3, 0, 0, reinterpret_cast<scm_t_subr>(&Display::scm_display_setup));
}

SCM
Display::scm_display_setup (SCM s_width, SCM s_height, SCM fullscreen)
{
  int width  = scm_to_int(s_width);
  int height = scm_to_int(s_height);

  std::cout << "Display::scm_display_setup: " << width << "x" << height << std::endl;

  //CL_Display::set_videomode (SCM_INUM (width), SCM_INUM (height), 32, false, false);
  // FIXME: Memory leak
  new CL_DisplayWindow("Advent Engine Test", width, height);

  std::cout << "Display::scm_display_setup: Done" << std::endl;

  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
