//  $Id: FadeOut.cc,v 1.2 2001/07/16 19:31:05 grumbel Exp $
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

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "AdvHook.hh"
#include "FadeOut.hh"

SCM   FadeOut::hook;
SCM   FadeOut::lambda;
float FadeOut::progress;
int   FadeOut::running;
bool  FadeOut::is_blackout;

void
FadeOut::init ()
{
  progress = 0;
  running = 0;
  is_blackout = false;
  gh_new_procedure1_0 ("c:adv:fade-in/out", FadeOut::fade_out);
  gh_new_procedure0_0 ("c:adv:fade-in", FadeOut::fade_in);
  gh_new_procedure0_0 ("c:adv:blackout", FadeOut::blackout);
}

SCM 
FadeOut::blackout ()
{
  is_blackout = true;
  return SCM_UNSPECIFIED;
}

SCM 
FadeOut::fade_out (SCM l)
{
  progress = 0.0f;
  running = 1;
  lambda = l;
  is_blackout = false;
  scm_protect_object (lambda);

  hook = AdvHook::make ();
  scm_protect_object (hook);
  return hook;
}

SCM
FadeOut::fade_in ()
{
  is_blackout = false;
  progress = 0.0f;
  running = -1;
  
  hook = AdvHook::make ();
  scm_protect_object (hook);
  return hook;
}

void 
FadeOut::update (float delta)
{
  if (running != 0)
    {
      progress += delta ;
  
      if (progress > 1.0f && running == 1) 
	{
	  progress = 0.0f;
	  running = -1;
	  gh_call0 (lambda);
	  scm_unprotect_object (lambda);
	}
      else if (progress > 1.0f && running == -1) 
	{
	  progress = 0.0f;
	  running = 0;
	  AdvHook::call_finish (hook);
	  scm_unprotect_object (hook);
	}
    }
}

void 
FadeOut::draw ()
{
  if (is_blackout)
    CL_Display::clear_display ();
  else
    {
      if (running != 0)
	{
	  float p = progress;
	  if (running == -1)
	    p = 1.0f-p;
      
	  CL_Display::fill_rect (0, 0,
				 (CL_Display::get_width ()/2) * p,
				 CL_Display::get_height (), 
				 0.0f, 0.0f, 0.0f);
	  CL_Display::fill_rect (CL_Display::get_width (), 0,
				 (CL_Display::get_width ()/2) + ((CL_Display::get_width ()/2) * (1-p)),
				 CL_Display::get_height (), 
				 0.0f, 0.0f, 0.0f);

	  CL_Display::fill_rect (0, (CL_Display::get_height ()/2) * p, 
				 CL_Display::get_width (),
				 0, 
				 0.0f, 0.0f, 0.0f);

	  CL_Display::fill_rect (0, CL_Display::get_height () - ((CL_Display::get_height ()/2) * p),
				 CL_Display::get_width (),
				 CL_Display::get_height (), 
				 0.0f, 0.0f, 0.0f);
	}
    }
}

/* EOF */
