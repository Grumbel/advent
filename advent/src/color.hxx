//  $Id: color.hxx,v 1.3 2003/02/23 17:07:47 grumbel Exp $
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

#ifndef COLOR_HXX
#define COLOR_HXX

#include <stdio.h>
#include <guile/gh.h>

class Color
{
private:

public:
  float r;
  float g;
  float b;
  float a;

  Color () {
    r = g = b = a = 0.0f;
  }
  
  Color (SCM scm_color) 
  {
    if (gh_length (scm_color) == 4)
      {
	r = gh_scm2double(gh_car(scm_color));
	g = gh_scm2double(gh_cadr(scm_color));
	b = gh_scm2double(gh_caddr(scm_color));
	a = gh_scm2double(gh_car(gh_cdddr(scm_color)));
      }
    else if (gh_length (scm_color) == 3)
      {
	r = gh_scm2double(gh_car(scm_color));
	g = gh_scm2double(gh_cadr(scm_color));
	b = gh_scm2double(gh_caddr(scm_color));
	a = 1.0;
      }
    else
      {
	puts ("Color: Invalid color format: ");
	gh_display (scm_color);
	gh_newline ();
      }
  }

  Color (float r_, float g_, float b_)
    : r (r_), g (g_), b (b_)
  {} 
};

#endif

/* EOF */
