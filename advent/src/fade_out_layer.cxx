//  $Id: fade_out_layer.cxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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
#include <ClanLib/display.h>

#include "scm_converter.hxx"
//#include "AdvHook.hh"
#include "fade_out_layer.hxx"
#include "util.hxx"

namespace Advent {

FadeOutLayer::FadeOutLayer ()
{
  progress = 0;
  running = 0;
  is_blackout = false;
}

FadeOutLayer::~FadeOutLayer ()
{
}

void
FadeOutLayer::register_guile_bindings ()
{
  gh_c_define_public_gsubr("c:fadeout-layer:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(&FadeOutLayer::scm_fadeout_layer_create));
  gh_c_define_public_gsubr("c:fadeout-layer:fade", 2, 0, 0, reinterpret_cast<scm_t_subr>(&FadeOutLayer::scm_fadeout_layer_fade));
  gh_c_define_public_gsubr("c:fadeout-layer:blackout", 1, 0, 0, reinterpret_cast<scm_t_subr>(&FadeOutLayer::scm_fadeout_layer_blackout));
  gh_c_define_public_gsubr("c:fadeout-layer:fade-in", 1, 0, 0, reinterpret_cast<scm_t_subr>(&FadeOutLayer::scm_fadeout_layer_fade_in));

  //gh_c_define_public_gsubr("c:fadeout-layer:fade-out", 2, 0, 0, reinterpret_cast<scm_t_subr>(&FadeOutLayer::scm_fadeout_layer_fade_out));
  //gh_c_define_public_gsubr("c:fadeout-layer:fade-in", 1, 0, 0,  reinterpret_cast<scm_t_subr>(&FadeOutLayer::scm_fade_in));
  //gh_c_define_public_gsubr("c:fadeout-layer:blackout", 1, 0, 0, reinterpret_cast<scm_t_subr>(&FadeOutLayer::scm_blackout));
}

SCM
FadeOutLayer::scm_fadeout_layer_blackout (SCM scm_layer)
{
  FadeOutLayer* layer = smobbox_cast<FadeOutLayer>(scm_layer);
  layer->is_blackout = true;
  return SCM_UNSPECIFIED;
}

SCM
FadeOutLayer::scm_fadeout_layer_create ()
{
  return LayerSmob::create(new FadeOutLayer ());
}

SCM
FadeOutLayer::scm_fadeout_layer_fade (SCM scm_layer, SCM lambda)
{
  FadeOutLayer* layer = smobbox_cast<FadeOutLayer>(scm_layer);
  layer->progress = 0.0f;
  layer->running = 1;
  layer->lambda.set_scm(lambda);
  layer->is_blackout = false;

  /*hook = AdvHook::make ();
    scm_protect_object (hook);
    return hook;*/
  return SCM_UNSPECIFIED;
}


SCM
FadeOutLayer::scm_fadeout_layer_fade_in (SCM scm_layer)
{
  FadeOutLayer* layer = smobbox_cast<FadeOutLayer>(scm_layer);
  layer->is_blackout = false;
  layer->progress = 0.0f;
  layer->running = -1;

#if 0
  hook = AdvHook::make ();
    scm_protect_object (hook);
    return hook;
#endif
  return SCM_UNSPECIFIED;
}

void
FadeOutLayer::update (float delta)
{
  if (running != 0)
    {
      progress += delta ;

      if (progress > 1.0f && running == 1)
	{
	  progress = 0.0f;
	  running = -1;
	  scm_call_0 (lambda.get_scm ());
	}
      else if (progress > 1.0f && running == -1)
	{
	  progress = 0.0f;
	  running = 0;
	  //AdvHook::call_finish (hook);
	  //scm_unprotect_object (hook);
	}
    }
}

void
FadeOutLayer::draw (boost::dummy_ptr<View>)
{
  if (is_blackout)
    CL_Display::clear ();
  else
    {
      if (running != 0)
	{
	  float p = progress;
	  if (running == -1)
	    p = 1.0f-p;

#if 0 // Sun Feb 23 17:32:21 2003
	  CL_Display::fill_rect (0, 0,
				 int((CL_Display::get_width ()/2) * p),
				 CL_Display::get_height (),
				 0.0f, 0.0f, 0.0f);
	  CL_Display::fill_rect (CL_Display::get_width (), 0,
				 (CL_Display::get_width ()/2) + ((CL_Display::get_width ()/2) * (1-p)),
				 CL_Display::get_height (),
				 0.0f, 0.0f, 0.0f);

	  CL_Display::fill_rect (0, int((CL_Display::get_height ()/2) * p),
				 CL_Display::get_width (),
				 0,
				 0.0f, 0.0f, 0.0f);

	  CL_Display::fill_rect (0, CL_Display::get_height () - ((CL_Display::get_height ()/2) * p),
				 CL_Display::get_width (),
				 CL_Display::get_height (),
				 0.0f, 0.0f, 0.0f);
#endif
	}
    }
}

} // namespace Advent

/* EOF */
