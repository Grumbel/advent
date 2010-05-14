//  $Id: helper.cc,v 1.2 2001/03/08 01:08:00 grumbel Exp $
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

#include "helper.hh"

AdventObj* scm2AdventObj (SCM smob)
{
  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  //GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(advobj->obj);
  return advobj->obj;
}

GuileAdventObj* scm2GuileAdventObj (SCM smob)
{
  //std::cout << "bla: " << smob << std::endl;
  AdventObjP* advobj = reinterpret_cast<AdventObjP*>(SCM_CDR (smob));
  //std::cout << "1Pointer: " << advobj << std::endl;
  GuileAdventObj* obj = dynamic_cast<GuileAdventObj*>(advobj->obj);
  //std::cout << "2Pointer: " << obj << std::endl;
  assert (obj);
  return obj;
}

/* EOF */
