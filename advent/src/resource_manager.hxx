//  $Id: resource_manager.hxx,v 1.2 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef RESOURCEMANAGER_HXX
#define RESOURCEMANAGER_HXX

#include <guile/gh.h>
#include <string>

namespace Advent {

class SurfaceSprite;

/**
   Example of resource identifer:
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   file:/home/ingo/test.png                  absolute-file
   file:images/test.png                      relative-file
   http:pingus.seul.org/~grumbel/image.png   web-url
   ftp:pingus.seul.org/images.png            ftp-url
   resource:resfile.scr:images.png           resourcefile

   Format:
   ~~~~~~~
   <Resource-Protokoll>:<Identifer>
   default is to fallback to the file protokoll
 */
class ResourceManager
{
private:
  static ResourceManager* instance_;
public:
  ResourceManager ();
  ~ResourceManager ();

  static ResourceManager* instance () { return instance_; }
  
  SCM get (const std::string& str);

private:
  /** FIXME: should belong to a factory pattern 
      Return a newly allocated sprite object */
  SurfaceSprite* get_sprite (const std::string& str);

private:
  static long tag;
public:
  static long get_smob_tag () { return tag; }

  static void register_guile_bindings ();
  static SCM scm_resourcemanager_get (SCM);
};

} // namespace Advent

#endif

/* EOF */
