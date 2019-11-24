//  $Id: button_layer.cxx,v 1.15 2004/01/14 02:28:24 grumbel Exp $
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

#include "debug.hxx"
#include "resource_manager.hxx"
#include "scm_converter.hxx"
#include "surface_sprite.hxx"
#include "button_layer.hxx"

namespace Advent {

ButtonLayer::ButtonLayer (SCM scm_sprite,
			  SCM scm_pressed_sprite,
			  SCM scm_mouse_over_sprite,
			  int arg_x_pos, int arg_y_pos)
  : sprite (scm_sprite),
    pressed_sprite (scm_pressed_sprite),
    mouse_over_sprite (scm_mouse_over_sprite),
    x_pos (arg_x_pos), y_pos (arg_y_pos),
    scm_on_press (SCM_BOOL_F)
{


  z_pos = 100.0f;
}

ButtonLayer::~ButtonLayer ()
{
}

void
ButtonLayer::update (float delta)
{
}

void
ButtonLayer::draw (boost::dummy_ptr<View> view)
{
  /*std::cout << "ButtonLayer::scm_buttonlayer_create: " << std::endl;
  scm_display (sprite.get_scm (), scm_current_output_port());
  scm_newline (scm_current_output_port());*/

  // FIXME: Using CL_Mouse directly is ugly
  if (is_over(CL_Mouse::get_x (), CL_Mouse::get_y())
      && mouse_over_sprite.get_scm() != SCM_BOOL_F)
    mouse_over_sprite.get ()->draw (view, CL_Vector (x_pos, y_pos));
  else
    sprite.get ()->draw (view, CL_Vector (x_pos, y_pos));
}

bool
ButtonLayer::is_over (int x, int y)
{
  return  (x > x_pos && x < x_pos + sprite.get ()->get_width ()
	   && y > y_pos && y < y_pos + sprite.get ()->get_height ());
}

void
ButtonLayer::on_button_press (const CL_InputEvent& key)
{
  if (scm_on_press.get_scm () != SCM_BOOL_F)
    {
      scm_call_0 (scm_on_press.get_scm ());
    }
  else
    {
      std::cout << "ButtonLayer: Button press is unbound" << std::endl;
    }
}

void
ButtonLayer::on_button_release (const CL_InputEvent&)
{
  if (scm_on_release.get_scm () != SCM_BOOL_F)
    {
      scm_call_0 (scm_on_release.get_scm ());
    }
  else
    {
      std::cout << "ButtonLayer: Button release is unbound" << std::endl;
    }
}

void
ButtonLayer::register_guile_bindings ()
{
  puts ("ButtonLayer::register_guile_bindings ()");

  scm_c_define_gsubr("c:buttonlayer:create", 5, 0, 0, reinterpret_cast<scm_t_subr>(&ButtonLayer::scm_buttonlayer_create));
  scm_c_define_gsubr("c:buttonlayer:set-press-callback", 2, 0, 0, reinterpret_cast<scm_t_subr>(&ButtonLayer::scm_buttonlayer_set_press_callback));
  scm_c_define_gsubr("c:buttonlayer:set-release-callback", 2, 0, 0, reinterpret_cast<scm_t_subr>(&ButtonLayer::scm_buttonlayer_set_release_callback));
}

/*
SCM
ButtonLayer::mark (SCM scm_button)
{
  ButtonLayer* button = smob_cast<ButtonLayer>(scm_button);
  button->sprite.mark ();
  return button->scm_on_press.get_scm ();
}*/

/*
int
ButtonLayer::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:ButtonLayer>", port);
  return 1;
}*/

SCM
ButtonLayer::scm_buttonlayer_create (SCM scm_sprite,
				     SCM scm_pressed_sprite,
				     SCM scm_mouse_over_sprite,
				     SCM x_pos, SCM y_pos)
{
  // FIXME: Add argument check here
  return LayerSmob::create(new ButtonLayer (scm_sprite,
					    scm_pressed_sprite,
					    scm_mouse_over_sprite,
					    scm_to_int (x_pos),
					    scm_to_int (y_pos)));
}

SCM
ButtonLayer::scm_buttonlayer_set_press_callback (SCM scm_button, SCM func)
{
  ButtonLayer* button = smobbox_cast<ButtonLayer>(scm_button);
  button->scm_on_press.set_scm (func);
  return SCM_UNSPECIFIED;
}

SCM
ButtonLayer::scm_buttonlayer_set_release_callback (SCM scm_button, SCM func)
{
  ButtonLayer* button = smobbox_cast<ButtonLayer>(scm_button);
  button->scm_on_release.set_scm (func);
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
