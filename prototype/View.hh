//  $Id: View.hh,v 1.2 2001/07/11 08:03:26 grumbel Exp $
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

#ifndef VIEW_HH
#define VIEW_HH

#include <ClanLib/core.h>
#include <guile/gh.h>
#include "Guy.hh"

class View;

extern View* the_view;

/** Yet Another View implementation... FIXME: Would multiple views be
 a good idea? Probally usefull for splitscreen... */
class View
{
private:
  // We follow this person if != 0
  Guy* guy;

public:

  // Information what should be drawn
  Scenario* scenario;

  int x_offset;
  int y_offset;
  //end

  View ();
  ~View ();

  void draw ();
  void update (float delta);
  void look_at (CL_Vector pos);
  void scroll_to (CL_Vector pos);
  void follow (Guy*);
  //void fade_out ();

  /***************/
  /* Guile Stuff */
  /***************/

  /** Init guile functions and smob staff */
  static void init ();

  /** Set the view to the given position */
  static SCM look_at (SCM x, SCM y);

  /** Scroll slowly to the given coordinates */
  static SCM scroll_to (SCM x, SCM y);

  /** Set the viem onto the given scenario */
  static SCM set_scenario (SCM scenario);

  /** Follow a person */
  static SCM follow (SCM person);

  /** Fadeout the screen */
  static SCM fade_out ();
};

#endif

/* EOF */
