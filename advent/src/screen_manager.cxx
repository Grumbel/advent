//  $Id: screen_manager.cxx,v 1.14 2004/01/14 02:28:24 grumbel Exp $
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

#include <ClanLib/display.h>
#include <ClanLib/core.h>
#include <ClanLib/gl.h>

#include "scm_converter.hxx"
#include "inventory.hxx"
#include "layer_screen.hxx"
#include "scenario_layer.hxx"
#include "screen_manager.hxx"
#include "button_layer.hxx"
#include "display_view.hxx"
#include "util.hxx"

namespace Advent {

ScreenManager* ScreenManager::instance_ = 0;

ScreenManager*
ScreenManager::instance()
{
  if (instance_)
    return instance_;
  else
    return (instance_ = new ScreenManager());
}

ScreenManager::ScreenManager ()
{
  puts ("123928098 input handling disabled"); //Sun Feb 23 17:20:51 2003

  on_mouse_press_slot   = CL_Mouse::sig_key_down().connect (this, &ScreenManager::on_button_press);
  on_mouse_release_slot = CL_Mouse::sig_key_up().connect (this, &ScreenManager::on_button_release);

  on_key_press_slot   = CL_Keyboard::sig_key_down().connect (this, &ScreenManager::on_button_press);
  on_key_release_slot = CL_Keyboard::sig_key_up().connect (this, &ScreenManager::on_button_release);
}

void
ScreenManager::update (float delta)
{
  current_screen->update (delta);
  CL_System::sleep (20);
}

void
ScreenManager::draw ()
{
  //static double angle = 0;
  std::cout << "ScreenManager::draw" << std::endl;
  DisplayView view (0,0, CL_Display::get_width (), CL_Display::get_height (),
		    -320,-240);
  CL_Display::clear(); // FIXME: Remove this at a later
				// point, could give you some more fps

  //std::cout << "Angle: " << angle << std::endl;
  //angle += 1.0f;

  /*
  glPushMatrix ();
  glTranslated (400, 300, 0.0);
  glRotated (angle, 0, 0, 1.0);
  glTranslated (-400, -300, 0.0);*/
  current_screen->draw (&view);
  //glPopMatrix ();

  CL_Display::flip();
}

void
ScreenManager::on_button_press (const CL_InputEvent& key)
{
  //std::cout << "ScreenManager::on_button_press (" << device << ", " << key.id << ")" << std::endl;
  current_screen->on_button_press (key);
}

void
ScreenManager::on_button_release (const CL_InputEvent& key)
{
  //std::cout << "ScreenManager::on_button_release (" << device << ", " << key.id << ")" << std::endl;
  current_screen->on_button_release (key);
}

void
ScreenManager::register_guile_bindings ()
{
  gh_c_define_public_gsubr("c:screenmanager:set-screen", 1, 0, 0, reinterpret_cast<scm_t_subr>(&ScreenManager::scm_screenmanager_set_screen));
}

SCM
ScreenManager::scm_screenmanager_set_screen (SCM scm_screen)
{
  Screen* screen = smobbox_cast<Screen>(scm_screen);
  ScreenManager::instance()->current_screen = screen;
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
