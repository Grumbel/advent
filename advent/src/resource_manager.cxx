//  $Id: resource_manager.cxx,v 1.3 2004/01/14 02:28:24 grumbel Exp $
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
#include "resource_manager.hxx"

namespace Advent {

ResourceManager* ResourceManager::instance_;

SCM
ResourceManager::get (const std::string& str)
{
  return SpriteSmob::create(get_sprite (str));
}

SurfaceSprite*
ResourceManager::get_sprite (const std::string& str)
{
  try {
    SurfaceSprite* tmp = new SurfaceSprite (str);
    return tmp;
  } catch (CL_Error& err) {
    std::cout << "ResourceManager:get: " << str << " not found." << std::endl;
  }
  try {
    return new SurfaceSprite ("images/404.png");
  } catch (CL_Error& err) {
    std::cout << "ResourceManager:get: 404 not found, fatal error." << std::endl;
    exit (1);
  }
}

void
ResourceManager::register_guile_bindings ()
{
  gh_new_procedure1_0("c:resourcemanager:get", ResourceManager::scm_resourcemanager_get);
}

SCM
ResourceManager::scm_resourcemanager_get (SCM resource_id)
{
  assert (gh_string_p (resource_id));
  // FIXME: Should be replaced with a factory pattern
  return ResourceManager::instance()->get (SCM_CHARS (resource_id));
}

} // namespace Advent

/* EOF */
