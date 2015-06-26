//  $Id: scm_converter.hxx,v 1.16 2003/02/24 22:41:55 grumbel Exp $
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

#ifndef SCMCONVERTER_HXX
#define SCMCONVERTER_HXX

#include <typeinfo>
#include <iostream>
#include <guile/gh.h>
#include <assert.h>

/** Convert an SCM into an Object pointer without any checking. Should
    only be used in an mark () function. */
template<class T>
T* unchecked_smob_cast(SCM smob)
{
  assert (SCM_NIMP (smob));
  T* obj = reinterpret_cast<T*>(SCM_CDR (smob));
  return obj;
}

#if 0
template<class T>
T* smob_cast(SCM smob)
{
  assert (!gh_boolean_p(smob));
  assert (SCM_NIMP (smob));

  /*
  if (smob_cast_checking_enabled && !T::is_a(smob)) {
    std::cout << ",----===================  Begin: ERROR =======================-----" << std::endl;
    std::cout << "| Cast error: " << typeid (T).name () << std::endl;
    //" tag: " << T::get_smob_tag () << std::endl;
    scm_puts ("| SCM Type: ", scm_current_output_port ());
    scm_display (smob, scm_current_output_port ());
    scm_newline (scm_current_output_port ());
    std::cout << "`----===================  End:   ERROR =======================-----" << std::endl;
    //assert (0);
    }
  */
  //std::cout << "smob_cast: " << SCM_CAR (smob) << std::endl;
  T* obj = reinterpret_cast<T*>(SCM_CDR (smob));
  return obj;
}
#endif

/* Type checking doesn't work correctly when downcasting from
   inherited types, so use smob_cast for that */
template<class T>
T* checked_smob_cast(SCM smob)
{
  assert (!gh_boolean_p(smob));
  if (SCM_NIMP (smob))
    {
      // Sun Feb 23 17:08:38 2003 might crash
      //puts ("99333 might crash"); seems to work
      if (long(SCM_CAR(smob)) == T::get_smob_tag ())
	{
	  T* obj = reinterpret_cast<T*>(SCM_CDR (smob));
	  return obj;
	}
      else
	{
	  std::cout << "Error: checked_smob_cast: expected (" << typeid (T).name() << ") "
		    << T::get_smob_tag ()
		    << " got " << SCM_CAR (smob) << std::endl;
	  assert (!"checked_smob_cast: Wrong cast");
	  return 0;
	}
    }
  else
    {
      std::cout << "Error: SCMConverter: cast error, not a smob" << std::endl;
      gh_display (smob); gh_newline ();
      return 0;
    }
}

template<class T>
bool check_type(SCM smob)
{
  return (SCM_NIMP (smob) && SCM_CAR (smob) == T::get_smob_tag ());
}

/** simple wrapper to create a smob without the need to return it */
template<class T>
SCM create_smob (long tag, T* data)
{
  SCM_RETURN_NEWSMOB(tag, data);
}

/** simple wrapper to create a smob without the need to return it */
template<class T>
SCM create_smob ()
{
  SCM_RETURN_NEWSMOB(T::get_smob_tag (), new T());
}

/** simple wrapper to create a smob without the need to return it */
template<class T>
SCM create_smob (T* data)
{
  SCM_RETURN_NEWSMOB(T::get_smob_tag (), data);
}

/** Cast a smob to the given type T or fail with an assert
    FIXME: Error handling should be more tolerant (guile assertion) */
template<class T>
T* smobbox_cast (SCM smob)
{
  T* t = dynamic_cast<T*>(T::cast(smob)->get_child ());
  if (t)
    return t;
  else
    {
      assert (!"Cast error1");
      return 0;
    }
}

/** Check if the smob is of the given type T */
template<class T>
bool smobbox_check (SCM smob)
{
  if (SCM_NIMP (smob) && (long)(SCM_CAR (smob)) == T::get_smob_tag ())
    {
      T* t = dynamic_cast<T*>(T::cast(smob)->get_child ());

      if (t)
	return true;
      else
	{
	  return false;
	}
    }
  else
    {
      return false;
    }
}

#endif

/* EOF */
