//  $Id: Drawabledisplay.cxx,v 1.14 2004/01/14 02:28:24 grumbel Exp $
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

#include "drawable_display.hxx"

namespace Advent {

namespace {
  struct z_pos_sorter 
  {
    bool operator() (SmobTuple<Drawable>& a,
		     SmobTuple<Drawable>& b)
    {
      //std::cout << "Sorter: " << a << " " << b << std::endl;
      return a.get()->get_z_pos () < b.get ()->get_z_pos ();
    }
  };
  
  struct drawable_removable
  {
    bool operator() (SmobTuple<Drawable>& a)
    {
      std::cout << "Removable checker called" << std::endl;
      return checked_smob_cast<DrawableSmob>(a.get_scm ())->get_child ()->is_removable ();
    }
  };
}

DrawableDisplay::DrawableDisplay ()
{
}

void
DrawableDisplay::add (SCM drawable)
{
  drawables.push_back (SmobTuple<Drawable>(drawable));
}

void 
DrawableDisplay::remove (SCM drawable)
{
  drawables.remove (SmobTuple<Drawable>(drawable));
}

void
DrawableDisplay::clear ()
{
  drawables = DrawableList ();
}

void 
DrawableDisplay::update (float delta)
{
  DrawableList tmp (drawables);
  for (DrawableList::iterator i = tmp.begin ();
       i != tmp.end (); ++i)
    {
      i->get ()->update (delta);
    }
}

void
DrawableDisplay::draw (boost::dummy_ptr<View> view)
{
  //std::cout << "DrawableDisplay::sorting start: " << drawables.size () << std::endl;
  drawables.sort (z_pos_sorter ());

  for (DrawableList::iterator i = drawables.begin ();
       i != drawables.end (); ++i)
    {
      //std::cout << "Drawing..." << std::endl;
      i->get ()->draw (view);
    }
}

void 
DrawableDisplay::mark ()
{
  for_each (drawables.begin (), drawables.end(),
	    std::mem_fun_ref (&SmobTuple<Drawable>::mark));
}

} // namespace Advent 

/* EOF */
