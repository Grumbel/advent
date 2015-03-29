//  $Id: layer_screen.cxx,v 1.22 2004/01/14 02:28:24 grumbel Exp $
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

#include <stdio.h>

#include "scm_converter.hxx"
#include "layer_screen.hxx"

namespace Advent {

struct z_pos_sorter
{
  bool operator () (SmobTuple<Layer>& a, SmobTuple<Layer>& b)
  {
    return a.get ()->get_z_pos () < b.get ()->get_z_pos ();
  }
};

LayerScreen::LayerScreen ()
{
  input_enabled = 1;
  lock_count = 0;

  //input_enabled_hook = SCM_BOOL_F;
  //input_disabled_hook = SCM_BOOL_F;

  //std::cout << "LayerScreen::LayerScreen ()" << std::endl;
}

LayerScreen::~LayerScreen ()
{
  //std::cout << "LayerScreen::~LayerScreen ()" << std::endl;
}

void
LayerScreen::update (float delta)
{
  LayerList tmp (layers);

  for (LayerList::iterator i = tmp.begin ();
       i != tmp.end (); ++i)
    {
      i->get ()->update (delta);
    }
}

void
LayerScreen::draw (boost::dummy_ptr<View> view)
{
  ++lock_count;
  for (LayerList::iterator i = layers.begin ();
       i != layers.end (); ++i)
    {
      i->get ()->draw (view);
    }
  --lock_count;
}

bool
LayerScreen::is_over (int x_pos, int y_pos)
{
  for (LayerList::iterator i = layers.begin ();
       i != layers.end (); ++i)
    {
      if (i->get ()->is_over (x_pos, y_pos))
	return true;
    }
  return false;
}

void
LayerScreen::on_button_press (const CL_InputEvent& key)
{
  if (input_enabled)
    {
      LayerList tmp (layers);

      for (LayerList::reverse_iterator i = tmp.rbegin ();
	   i != tmp.rend (); ++i)
	{
	  if (i->get ()->is_over ((int) key.mouse_pos.x, (int) key.mouse_pos.y))
	    {
	      i->get ()->on_button_press (key);
	      return;
	    }
	}
    }
}

void
LayerScreen::on_button_release (const CL_InputEvent& key)
{
  if (input_enabled)
    {
      LayerList tmp (layers);

      for (LayerList::reverse_iterator i = tmp.rbegin ();
	   i != tmp.rend (); ++i)
	{
	  if (i->get ()->is_over ((int) key.mouse_pos.x, (int) key.mouse_pos.y))
	    {
	      i->get ()->on_button_release (key);
	      return;
	    }
	}
    }
}

void
LayerScreen::pop ()
{
  assert (lock_count == 0);
  layers.pop_back ();
  layers.sort (z_pos_sorter ());
}

void
LayerScreen::push (SCM layer)
{
  assert (lock_count == 0);
  layers.push_back (SmobTuple<Layer>(layer));
  layers.sort (z_pos_sorter ());

}

void
LayerScreen::remove (SCM obj)
{
  std::cout << "before Trying remove: " << layers.size () << std::endl;
  layers.remove (SmobTuple<Layer>(obj));
  std::cout << "end Trying remove: " << layers.size () << std::endl;
}

void
LayerScreen::register_guile_bindings ()
{
  puts ("LayerScreen::register_guile_bindings ()");

  gh_new_procedure0_0 ("c:layerscreen:create", &LayerScreen::layerscreen_create);
  gh_new_procedure2_0 ("c:layerscreen:push", &LayerScreen::layerscreen_push);
  gh_new_procedure2_0 ("c:layerscreen:remove", &LayerScreen::layerscreen_remove);
  gh_new_procedure1_0 ("c:layerscreen:pop", &LayerScreen::layerscreen_pop);
  gh_new_procedure1_0 ("c:layerscreen:enable-input",
		       &LayerScreen::layerscreen_enable_input);
  gh_new_procedure1_0 ("c:layerscreen:disable-input",
		       &LayerScreen::layerscreen_disable_input);
  gh_new_procedure2_0 ("c:layerscreen:set-input-enabled-hook",
		       &LayerScreen::layerscreen_set_input_enabled_hook);
  gh_new_procedure2_0 ("c:layerscreen:set-input-disabled-hook",
		       &LayerScreen::layerscreen_set_input_disabled_hook);
}

/*
SCM
LayerScreen::mark (SCM smob)
{
  LayerScreen* layer = smob_cast<LayerScreen>(smob);

  for (LayerList::reverse_iterator i = layer->layers.rbegin ();
       i != layer->layers.rend (); ++i)
    {
      i->mark ();
    }
  return SCM_BOOL_F;
}

scm_sizet
LayerScreen::free (SCM smob)
{
  std::cout << "LayerScreen::free" << std::endl;
  delete smob_cast<LayerScreen>(smob);
  return 0; //sizeof (LayerScreen);
}

int
LayerScreen::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:LayerScreen>", port);
  return 1;
}
*/
SCM
LayerScreen::layerscreen_create ()
{
  LayerScreen* screen = new LayerScreen ();
  return LayerSmob::create (screen);
}

SCM
LayerScreen::layerscreen_push (SCM scm_screen, SCM scm_layer)
{
  LayerScreen* screen = smobbox_cast<LayerScreen>(scm_screen);
  screen->push (scm_layer);
  return SCM_UNSPECIFIED;
}

SCM
LayerScreen::layerscreen_remove (SCM scm_screen, SCM scm_layer)
{
  LayerScreen* screen = smobbox_cast<LayerScreen>(scm_screen);
  screen->remove (scm_layer);
  return SCM_UNSPECIFIED;
}

SCM
LayerScreen::layerscreen_pop (SCM scm_screen)
{
  LayerScreen* screen = smobbox_cast<LayerScreen>(scm_screen);
  screen->pop ();
  return SCM_UNSPECIFIED;
}

SCM
LayerScreen::layerscreen_enable_input (SCM scm_screen)
{
  LayerScreen* screen = smobbox_cast<LayerScreen>(scm_screen);
  screen->input_enabled += 1;

  if (screen->input_enabled == 1
      &&
      screen->input_enabled_hook.get_scm () != SCM_BOOL_F)
    {
      gh_call0 (screen->input_enabled_hook.get_scm ());
    }

  return SCM_UNSPECIFIED;
}

SCM
LayerScreen::layerscreen_disable_input (SCM scm_screen)
{
  LayerScreen* screen = smobbox_cast<LayerScreen>(scm_screen);
  screen->input_enabled -= 1;

  if (screen->input_enabled == 0
      &&
      screen->input_enabled_hook.get_scm () != SCM_BOOL_F)
    {
      gh_call0 (screen->input_disabled_hook.get_scm ());
    }

  return SCM_UNSPECIFIED;
}

SCM
LayerScreen::layerscreen_set_input_enabled_hook (SCM scm_screen, SCM scm_hook)
{
  LayerScreen* screen = smobbox_cast<LayerScreen>(scm_screen);
  screen->input_enabled_hook.set_scm (scm_hook);
  return SCM_UNSPECIFIED;
}

SCM
LayerScreen::layerscreen_set_input_disabled_hook (SCM scm_screen, SCM scm_hook)
{
  LayerScreen* screen = smobbox_cast<LayerScreen>(scm_screen);
  screen->input_disabled_hook.set_scm (scm_hook);
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
