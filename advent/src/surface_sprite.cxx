//  $Id: Surfacesprite.cxx,v 1.25 2004/01/14 02:28:24 grumbel Exp $
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
#include "util.hxx"

namespace Advent {

SurfaceSprite::SurfaceSprite (std::string arg_filename)
  : filename (arg_filename), frame (0.0f), fps (15.0f)
{
  //std::cout << "SurfaceSprite::SurfaceSprite" << std::endl;
  try {
    // FIXME: Replace this with a resource handler
    CL_PixelBuffer provider;
    if (filename.substr (filename.length () - 4) == ".png")
      provider = CL_PNGProvider (filename.c_str ());
    else if (filename.substr (filename.length () - 4) == ".jpg")
      provider = CL_JPEGProvider (filename.c_str ());
    else if (filename.substr (filename.length () - 4) == ".tga")
      provider = CL_TargaProvider (filename.c_str (), NULL);
    else if (filename.substr (filename.length () - 4) == ".pcx")
      provider = CL_PCXProvider (filename.c_str (), NULL);
    else
      {
	std::cout << "Unknown imagefile extension: '"
		  << filename.substr (filename.length () - 4) << "'" << std::endl;
	assert (0);
      }

    provider.lock();
    std::cout << "Sprite: " << filename << ": "
              << provider.get_width() << "x" << provider.get_height() << std::endl;

    if (provider.get_width() >= 1024)
      {
        std::cout << "SurfaceSprite: Warning sprite '" << filename
                  << "' will get truncated to 1024 pixels" << std::endl;
        // FIXME: Little hack to make large backgrounds loadable
        CL_SpriteDescription desc;
        // FIXME: Memory leak, add resource manager here
        desc.add_gridclipped_frames(provider, 0, 0, 1024, provider.get_height());
        sprite = CL_Sprite (desc);
      }
    else
      {
        CL_SpriteDescription desc;
        desc.add_frame(provider);
        sprite = CL_Sprite (desc);
      }

    provider.unlock();
  } catch (const CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
    assert (0);
  }

  animated = false;
}

SurfaceSprite::SurfaceSprite (std::string arg_filename, int frames)
  : filename (arg_filename), frame (0.0f), fps (15)
{
  //std::cout << "SurfaceSprite::SurfaceSprite" << std::endl;
  try {
    // FIXME: Replace this with a resource handler
    CL_PixelBuffer provider = CL_PNGProvider (filename.c_str ());
    provider.lock ();

    if (provider.get_width () % frames)
      {
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "SurfaceSprite: Width not divideable by frames" << std::endl;
	std::cout << "SurfaceSprite: width=" << provider.get_width ()
		  << " frames=" << provider.get_height () << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
      }

    CL_SpriteDescription desc;
    // FIXME: Memory leak, add resource manager here
    desc.add_gridclipped_frames(provider,
                                0, 0, // x, y
                                provider.get_width()/frames, provider.get_height(), // width, height
                                frames, 1); // xarray, yarray
    sprite = CL_Sprite (desc);

    provider.unlock ();
  } catch (const CL_Error& err) {
    std::cout << "CL_Error: " << err.message << std::endl;
    assert (0);
  }
}

SurfaceSprite::~SurfaceSprite ()
{
  //std::cout << "SurfaceSprite::~SurfaceSprite" << std::endl;
}

void
SurfaceSprite::set_fps (float arg_fps)
{
  fps = arg_fps;
}

void
SurfaceSprite::update (float delta)
{
  sprite.update(delta);
}

void
SurfaceSprite::draw (boost::dummy_ptr<View> view, const CL_Vector& pos)
{
  view->draw(sprite, int(pos.x), int(pos.y));
}

void
SurfaceSprite::draw (boost::dummy_ptr<View> view, const CL_Vector& pos, float zoom)
{
  sprite.set_scale (zoom, zoom);
  view->draw (sprite,
              int(pos.x),
              int(pos.y));
}

void
SurfaceSprite::set_align_center_bottom()
{
  sprite.set_alignment (origin_bottom_center);
}

void
SurfaceSprite::set_align (int x, int y)
{
  sprite.set_alignment (origin_top_left, x, -y);
}

void
SurfaceSprite::set_align_center ()
{
  sprite.set_alignment (origin_center);
}

void
SurfaceSprite::register_guile_bindings ()
{
  puts ("SurfaceSprite::register_guile_bindings ()");

  scm_c_define_gsubr("c:surface-sprite:create", 1, 0, 0, reinterpret_cast<scm_t_subr>(&SurfaceSprite::scm_surface_sprite_create));
  scm_c_define_gsubr("c:surface-sprite:create-anim", 2, 0, 0, reinterpret_cast<scm_t_subr>(&SurfaceSprite::scm_surface_sprite_create_anim));

  scm_c_define_gsubr("c:surface-sprite:set-align-center", 1, 0, 0, reinterpret_cast<scm_t_subr>(&SurfaceSprite::scm_surface_sprite_set_align_center));
  scm_c_define_gsubr("c:surface-sprite:set-align", 3, 0, 0, reinterpret_cast<scm_t_subr>(&SurfaceSprite::scm_surface_sprite_set_align));
  scm_c_define_gsubr("c:surface-sprite:set-fps", 2, 0, 0, reinterpret_cast<scm_t_subr>(&SurfaceSprite::scm_surface_sprite_set_fps));
}

SCM
SurfaceSprite::scm_surface_sprite_create (SCM name)
{
  assert (scm_is_string (name));
  return SpriteSmob::create(new SurfaceSprite (scm_to_cxxstring (name)));
}

SCM
SurfaceSprite::scm_surface_sprite_create_anim (SCM name, SCM frames)
{
  return SpriteSmob::create (new SurfaceSprite (scm_to_cxxstring (name),
						scm_to_int (frames)));
}

SCM
SurfaceSprite::scm_surface_sprite_set_align_center (SCM scm_sprite)
{
  smobbox_cast<SurfaceSprite>(scm_sprite)->set_align_center ();
  return scm_sprite;
}

SCM
SurfaceSprite::scm_surface_sprite_set_align (SCM scm_sprite, SCM scm_x, SCM scm_y)
{
  smobbox_cast<SurfaceSprite>(scm_sprite)->set_align (scm_to_int (scm_x),
						      scm_to_int (scm_y));
  return scm_sprite;
}

SCM
SurfaceSprite::scm_surface_sprite_set_fps (SCM scm_sprite, SCM scm_fps)
{
  smobbox_cast<SurfaceSprite>(scm_sprite)->set_fps (scm_to_double(scm_fps));
  return scm_sprite;
}

} // namespace Advent

/* EOF */
