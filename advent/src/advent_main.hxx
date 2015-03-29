//  $Id: advent_main.hxx,v 1.5 2004/01/14 02:28:24 grumbel Exp $
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

#ifndef ADVENTMAIN_HH
#define ADVENTMAIN_HH

#include "layer_group.hxx"

extern "C" {
  void scm_init_advent_core_module ();
}

namespace Advent {

class AdventMain
{
private:

public:
  char* get_title ();
  void  parse_args (int argc, char* argv[]);

  void  register_guile_bindings ();

  void  init_advent ();
  void  deinit_advent ();
  void  main_loop ();


  int   main (int argc, char* argv[]);
  int   inner_main (void* closure, int argc, char* argv[]);
} app;

// Wrapper to call the member func
void inner_main (void* closure, int argc, char* argv[])
{
  app.inner_main (closure, argc, argv);
}

} // namespace Advent

#endif

/* EOF */
