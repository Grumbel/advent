//  $Id: screen_manager.hxx,v 1.7 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef SCREENMANAGER_HXX
#define SCREENMANAGER_HXX

#include <list>
#include <libguile.h>
#include "boost/smart_ptr.hpp"
#include "screen.hxx"

namespace Advent {

/** This is basically where the mainloop takes place */
class ScreenManager
{
private:
  Screen* current_screen;

  CL_Slot on_key_press_slot;
  CL_Slot on_key_release_slot;

  CL_Slot on_mouse_press_slot;
  CL_Slot on_mouse_release_slot;

  static ScreenManager* instance_;
public:
  static ScreenManager* instance();

  ScreenManager ();
  void update (float delta);
  void draw ();

  /** FIXME: We should probally use a Controller interface here (could
      be usefull for two player mode or something like that [Spy vs.
      Spy])*/
  void on_button_press (const CL_InputEvent&);
  void on_button_release (const CL_InputEvent&);

  // static guile stuff
public:
  static void register_guile_bindings ();
  static SCM scm_screenmanager_set_screen (SCM scm_screen);
};

} // namespace Advent

#endif

/* EOF */
