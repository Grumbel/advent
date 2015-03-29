//  $Id: FadeOut.hh,v 1.2 2001/07/16 19:31:05 grumbel Exp $
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

#ifndef FADEOUT_HH
#define FADEOUT_HH

#include <guile/gh.h>

class FadeOut
{
private:
  /** Called once the screen is fadeout */
  static SCM lambda;

  /** Called once the screen is faded back in */
  static SCM hook;

  static float progress;
  static int running;
  static bool is_blackout;
public:
  static void update (float delta);
  static void draw ();

  static void init ();
  static SCM fade_out (SCM l);
  static SCM fade_in ();

  static SCM blackout ();
};

#endif

/* EOF */
