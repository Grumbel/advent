//  $Id: Drawableadv_obj.cxx,v 1.9 2004/01/14 02:28:24 grumbel Exp $
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

#include "scm_converter.hxx"
#include "drawable_adv_obj.hxx"

namespace Advent {

DrawableAdvObj::DrawableAdvObj (SCM bind, SCM scm_drawable, SCM scm_collideable)
  : AdvObj (bind), drawable (scm_drawable), collideable (scm_collideable)
{}

void
DrawableAdvObj::update (float delta)
{
  drawable.get ()->update (delta);
  collideable.get ()->update (delta);
}

void
DrawableAdvObj::draw (boost::dummy_ptr<View> view) 
{ 
  drawable.get ()->draw (view);
}

bool 
DrawableAdvObj::is_over (int x_pos, int y_pos) 
{
  return collideable.get ()->is_over (x_pos, y_pos); 
}

float 
DrawableAdvObj::get_z_pos ()
{
  return drawable.get ()->get_z_pos (); 
}

void 
DrawableAdvObj::register_guile_bindings ()
{
  puts ("DrawableAdvObj::register_guile_bindings ()");

  gh_new_procedure3_0 ("c:drawable-advobj:create", &DrawableAdvObj::drawable_advobj_create);
  gh_new_procedure2_0 ("c:drawable-advobj:set-drawable", &DrawableAdvObj::drawable_advobj_set_drawable);
}

/*
SCM 
DrawableAdvObj::mark (SCM smob) 
{
  DrawableAdvObj* obj = smob_cast<DrawableAdvObj>(smob);
  obj->drawable.mark ();
  obj->collideable.mark ();
  return SCM_UNSPECIFIED;
}*/

/*int
DrawableAdvObj::print (SCM image_smob, SCM port, scm_print_state *pstate) 
{
  scm_puts ("#<c:DrawableAdvObj>", port);
  return 1;
}*/

SCM 
DrawableAdvObj::drawable_advobj_create (SCM bind, SCM scm_drawable, SCM scm_collideable)
{
  return DrawableSmob::create(new DrawableAdvObj (bind, scm_drawable, scm_collideable)); 
}

SCM 
DrawableAdvObj::drawable_advobj_set_drawable (SCM scm_obj, SCM scm_drawable)
{
  smobbox_cast<DrawableAdvObj>(scm_obj)->drawable.set_scm (scm_drawable);
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
