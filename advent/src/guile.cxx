//  $Id: guile.cxx,v 1.2 2001/10/15 18:13:24 grumbel Exp $
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

#include <iostream>
#include "guile.hxx"
#include <map>

int protect_counter = 0;

SCM
Guile::protect_object (SCM obj)
{
#ifdef DEBUG
  ++protect_counter;
#endif
  return scm_gc_protect_object (obj);
}

SCM
Guile::unprotect_object (SCM obj)
{
#ifdef DEBUG
  --protect_counter;

  std::cout << "Guile::unprotect_object: " << protect_counter << std::endl;

  SCM handle = scm_hashq_get_handle (scm_protects, obj);

  std::cout << "Handle: " << std::endl;
  scm_display(handle, scm_current_output_port());
  scm_newline(scm_current_output_port());

  scm_display(obj, scm_current_output_port());
  scm_newline(scm_current_output_port());
#endif
  return scm_gc_unprotect_object (obj);
  return obj;
}

/* EOF */
