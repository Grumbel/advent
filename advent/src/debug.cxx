//  $Id: debug.cxx,v 1.1 2001/09/20 20:02:35 grumbel Exp $
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

#include "debug.hxx"

bool Debug::free_enabled_ = false;

void
Debug::register_guile_bindings ()
{
  gh_new_procedure1_0 ("debug:set-free", scm_set_memory_free);
}

SCM
Debug::scm_set_memory_free (SCM value)
{
  set_free_enabled (gh_scm2bool (value));
  return SCM_UNSPECIFIED;
}

/* EOF */
