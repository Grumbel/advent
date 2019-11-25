//  $Id: coin_layer.cxx,v 1.13 2004/01/14 02:28:24 grumbel Exp $
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

#include "scm_converter.hxx"
#include "surface_sprite.hxx"
#include "coin_layer.hxx"
#include "util.hxx"

namespace Advent {

long CoinLayer::tag;

CoinLayer::CoinLayer ()
  : sprite (new SurfaceSprite ("images/coin.png")),
    click_func (SCM_BOOL_F),
    object (SCM_BOOL_F)
{
  sprite->set_align_center ();
  is_enabled = false;
}

CoinLayer::~CoinLayer ()
{
}


void
CoinLayer::update (float delta)
{
}

void
CoinLayer::draw (boost::dummy_ptr<View> view)
{
  if (is_enabled)
    sprite->draw (view, pos);
}

void
CoinLayer::enable (SCM obj)
{
  is_enabled = true;

  pos = CL_Vector (CL_Mouse::get_x (), CL_Mouse::get_y ());

  object.set_scm(obj);
}

void
CoinLayer::disable ()
{
  object.set_scm (SCM_BOOL_F);
  is_enabled = false;
}

bool
CoinLayer::is_over(int, int)
{
  if (is_enabled)
    return true;
  else
    return false;
}

void
CoinLayer::on_button_press(const CL_InputEvent& key)
{
  CL_Vector offset = CL_Vector (key.mouse_pos.x, key.mouse_pos.y) - pos;

  if (offset.norm () < 80.0)
    {
      //std::cout << "Offset:" << offset << std::endl;
      call_action (offset);
    }
  else
    {
      //std::cout << "Out of coin region" << std::endl;
    }
  disable ();
}

void
CoinLayer::call_action (const CL_Vector& offset)
{
  if (click_func.get_scm () != SCM_BOOL_F)
    scm_call_3 (click_func.get_scm (), object.get_scm (),
                scm_from_double (offset.x), scm_from_double (offset.y));
}

void
CoinLayer::on_button_release(const CL_InputEvent&)
{
}

void
CoinLayer::set_click_func (SCM func)
{
  click_func.set_scm(func);
}

void
CoinLayer::register_guile_bindings ()
{
  puts ("CoinLayer::register_guile_bindings ()");

  gh_c_define_public_gsubr("c:coinlayer:create", 0, 0, 0, reinterpret_cast<scm_t_subr>(&CoinLayer::scm_coinlayer_create));

  gh_c_define_public_gsubr("c:coinlayer:enable", 2, 0, 0, reinterpret_cast<scm_t_subr>(&CoinLayer::scm_coinlayer_enable));
  gh_c_define_public_gsubr("c:coinlayer:disable", 1, 0, 0, reinterpret_cast<scm_t_subr>(&CoinLayer::scm_coinlayer_disable));

  gh_c_define_public_gsubr("c:coinlayer:set-click-func", 2, 0, 0, reinterpret_cast<scm_t_subr>(&CoinLayer::scm_coinlayer_set_click_func));
}

/*
SCM
CoinLayer::mark (SCM smob)
{
  CoinLayer* layer = unchecked_smob_cast<CoinLayer>(smob);
  scm_gc_mark (layer->object.get_scm ());
  return layer->click_func.get_scm ();
}

size_t
CoinLayer::free (SCM smob)
{
  delete unchecked_smob_cast<CoinLayer>(smob);
  return 0; //sizeof (CoinLayer);
}

int
CoinLayer::print (SCM image_smob, SCM port, scm_print_state *pstate)
{
  scm_puts ("#<c:CoinLayer>", port);
  return 1;
}*/

SCM
CoinLayer::scm_coinlayer_create ()
{
  return LayerSmob::create (new CoinLayer ());
}

SCM
CoinLayer::scm_coinlayer_enable (SCM scm_layer, SCM obj)
{
  CoinLayer* layer = smobbox_cast<CoinLayer>(scm_layer);
  layer->enable (obj);
  return SCM_UNSPECIFIED;
}

SCM
CoinLayer::scm_coinlayer_disable (SCM scm_layer)
{
  CoinLayer* layer = smobbox_cast<CoinLayer>(scm_layer);
  layer->disable ();
  return SCM_UNSPECIFIED;
}

SCM
CoinLayer::scm_coinlayer_set_click_func (SCM scm_layer, SCM func)
{
  CoinLayer* layer = smobbox_cast<CoinLayer>(scm_layer);
  layer->set_click_func (func);
  return SCM_UNSPECIFIED;
}

} // namespace Advent

/* EOF */
