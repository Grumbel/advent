//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_OBJECT_ID_MANAGER_HXX
#define HEADER_OBJECT_ID_MANAGER_HXX

#include <vector>
#include "drawable.hxx"

/** Template class which maps objects to id's and id's to objects */
template<class T>
class ObjectIdManager
{
public:
  typedef std::vector<T*> Objects;
  Objects objects;

public:
  ObjectIdManager() {}
  ~ObjectIdManager() {}

  T* get_by_id(int id)
  {
    if (id >= 0 && id < int(objects.size()))
      return objects[id];
    else
      return 0;  
  }

  int get_id(T* obj)
  {
    for (typename Objects::iterator i = objects.begin(); i != objects.end(); ++i)
      {
        if (*i == obj)
          return (i - objects.begin());
      }
    return -1;
  }

  /** Add a newly created T to the manager and let it be
      managed by it (ie delete it if no longer needed) */
  int add(T* drawable) {
    int id = objects.size();
    objects.push_back(drawable);
    return id;
  }
};

#endif

/* EOF */
