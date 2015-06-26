//  $Id: valid.hxx,v 1.1 2002/04/23 12:34:36 grumbel Exp $
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

#ifndef VALID_HXX
#define VALID_HXX

/** Wrapper around some class which carries a bool flag in addition to
    the data from the object */
template<class T>
class Valid
{
private:
  T obj;
  bool valid;
public:
  Valid (T arg, bool arg_valid)
    : obj (arg), valid (arg_valid)
  {}

  Valid (bool arg_valid)
    : valid (arg_valid)
  {}

  bool is_valid () { return valid; }
  operator T () { return obj; }
  T& get () { return obj; }
};

#endif

/* EOF */
