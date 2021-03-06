//  $Id: Interpreter.cc,v 1.3 2001/08/21 20:38:43 grumbel Exp $
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
#include <string>
#include <guile/gh.h>
#include "Interpreter.hh"

 Interpreter interpreter;

Interpreter::Interpreter ()
{
}

Interpreter::~Interpreter ()
{
}

void
Interpreter::launch ()
{
  std::cout << "\n\n..:: Advent Interpreter V0.0 ::.." << std::endl;

  bool quit = false;
  while (!quit)
    {
      std::string line;

      std::cout << ">>> " << std::flush;
      getline (cin, line);

      if (line == "quit")
	quit = true;
      else
	{
	  line = "(catch #t (lambda () "
	    + line
	    + ") (lambda stuff (display \"Error: \") (display stuff) (newline)))";
	  SCM ret = gh_eval_str (line.c_str ());
	  if (ret != SCM_UNSPECIFIED)
	    {
	      gh_display(ret);
	      gh_newline ();
	    }
	}
    }
  std::cout << "Interpreter quited" << std::endl;
}

/* EOF */
