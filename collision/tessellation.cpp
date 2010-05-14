/*
	Init display example.
*/

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>

double two_pi = 6.283185307179586476925286766559005768394338798750211641949889184615632;
double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
double half_pi = 1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412671058534;

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
  bool is_valid () { return valid; }
  operator T () { return obj; }
};

Valid<CL_Vector> intersec (CL_Vector a1, CL_Vector a2,
			   CL_Vector b1, CL_Vector b2)
{
  CL_Vector a = a1;
  CL_Vector b = a2 - a1;

  CL_Vector c = b1;
  CL_Vector d = b2 - b1;

  CL_Vector col;

  double lambda;
  double mu;

  lambda = (c.y*d.x - c.x*d.y) + (a.x*d.y - a.y*d.x);
  lambda /= (b.y*d.x - b.x*d.y);
  
  mu = (a.x + (lambda * b.x) - c.x) / d.x;

  c = a + b*lambda;
  
  return Valid<CL_Vector>(c, true);
}
  
float pol_angle (const CL_Vector& vec) 
{
  if (vec.x > 0.0)
    return atan (vec.y/vec.x) + pi;
  else if (vec.x < 0.0) 
    return atan (vec.y/vec.x);
  else if (vec.y > 0.0)
    return half_pi;
  else if (vec.y < 0.0)
    return -half_pi;
  else
    return 0.0;
}


std::list<CL_Vector>::iterator
find_next (std::list<CL_Vector>::iterator a, std::list<CL_Vector>& lst)
{
  ++a;
  if (a == lst.end ())
    return lst.begin ();
  return a;
}

std::list<CL_Vector>::iterator
find_previous (std::list<CL_Vector>::iterator a, std::list<CL_Vector>& lst)
{
  if (a == lst.begin ())
    {
      a = lst.end ();
      --a;
      return a;
    }
  return --a;
}

class Polygon
{
public:
  std::list<CL_Vector> points;
  bool finished;
  
  float is_in_angle (float x, float y) 
  {
    CL_Vector mouse (x, y);
    double complete_angle = 0.0;

    for (std::list<CL_Vector>::iterator i = points.begin ();
	 i != points.end (); ++i)
      {
	std::list<CL_Vector>::iterator next = i;
	++next;
	if (next == points.end ())
	  next = points.begin ();
	
	CL_Vector a = *i - mouse;
	CL_Vector b = *next - mouse;
	
	complete_angle += a.angle (b);
      }
    
    //std::cout << "Angle: " << complete_angle << std::endl;
    return complete_angle;
  }
  
  bool is_in (float x, float y) 
  {
    double epsilon = 0.001;
    double complete_angle = is_in_angle (x, y);
    
    //std::cout << "complete_angle: " << complete_angle <<std::endl;

    if ((complete_angle < two_pi + epsilon) && (complete_angle > two_pi - epsilon))
      {
	//std::cout << "IS IN" << std::endl;
	return true;
      }
    else
      {
	//std::cout << "IS NOT IN" << std::endl;
	return false;  
      }
  }

  void draw (bool many)
  {
    for (std::list<CL_Vector>::iterator i = points.begin ();
	 i != points.end (); ++i)
      {
	std::list<CL_Vector>::iterator next = i;
	++next;
	if (next == points.end ())
	  next = points.begin ();

	if (many)
	  CL_Display::draw_line (i->x, i->y, next->x, next->y,
				 1.0, 0.0, .5);
	else if (next == points.begin () && !finished)
	  CL_Display::draw_line (i->x, i->y, next->x, next->y,
				 1.0, 1.0, 0.4);
	else
	  CL_Display::draw_line (i->x, i->y, next->x, next->y,
				 1.0, 1.0, 1.0);

      }
  }

  bool convex ()
  {
    if (points.size () < 3)
      {
	std::cout << "Invalid polygon!" << std::endl;
	return true;
      }

    for (std::list<CL_Vector>::iterator i = points.begin ();
	 i != points.end (); ++i)
      {
	std::list<CL_Vector>::iterator next = find_next (i, points);
	std::list<CL_Vector>::iterator previous = find_previous (i, points);

 	CL_Vector a = *previous - *i;
 	CL_Vector b = *next - *i;

 	float angle = fmod(pol_angle (b) - pol_angle (a) + two_pi, two_pi);
 	
	//std::cout << "Angle: " << angle/pi*180 << std::endl;
	if (angle > pi)
	  return false;
      }

    return true;
  }

  std::list<Polygon> tessellate ()
  {
    return tessellate (*this);
  }

  
  std::list<Polygon> tessellate (Polygon polygon, 
				 std::list<Polygon> rest = std::list<Polygon>())
  {
    int recursion = 0;
    std::cout << "------------- tessellate ---------------" << std::endl;
    std::list<CL_Vector>::iterator node = polygon.points.begin ();
    while (!polygon.convex () && recursion != 500)
      {
	++recursion;
	std::list<CL_Vector>::iterator next = find_next (node, points);
	std::list<CL_Vector>::iterator previous = find_previous (node, points);

 	CL_Vector a = *previous - *node;
 	CL_Vector b = *next - *node;
 	float angle = fmod(pol_angle (b) - pol_angle (a) + two_pi, two_pi);
	std::cout << "angle: " << angle << std::endl;		
	if (angle < pi) // convex
	  {
	    Polygon p;
	    p.points.push_back (*previous);
	    p.points.push_back (*node);
	    p.points.push_back (*next);
	    
	    // check for overlapping
	    bool is_overlapping = false;
	    for (std::list<CL_Vector>::iterator i = polygon.points.begin();
		 i != polygon.points.end (); ++i)
	      {
		if (p.is_in (i->x, i->y))
		  {
		    is_overlapping = true;
		    break;
		  }
	      }
	    if (!is_overlapping)
	      {
		rest.push_back (p);
		node = polygon.points.erase (node);
	      }
	    ++node;
	  }
	else
	  {
	    ++node;
	  }
	
	if (node == polygon.points.end ())
	  node = polygon.points.begin ();
      }
    
    if (recursion == 500)
      std::cout << "Recursion overflow, bail out" << std::endl;

    rest.push_back (polygon);
    std::cout << "Tessellation: " << rest.size () << std::endl;
    return rest;
  }
};

class InitDisplayApp : public CL_ClanApplication
{
public:
  virtual char *get_title() { return "InitDisplay application"; }

  CL_Surface create_colmap2 (Polygon polygon)
  {
    CL_Canvas* canvas = new CL_Canvas (CL_Display::get_width (), CL_Display::get_height ());
    
    canvas->lock ();
    for (int y = 0; y < CL_Display::get_height (); ++y)
      for (int x = 0; x < CL_Display::get_width (); ++x)
	{
	  canvas->draw_pixel (x, y,
			      polygon.is_in_angle (x, y) / two_pi,
			      polygon.is_in_angle (x, y) / two_pi,
			      polygon.is_in_angle (x, y) / two_pi);
	}
    canvas->unlock ();

    return CL_Surface (canvas, true);    
  }

  CL_Surface create_colmap (std::list<Polygon> polygons)
  {
    CL_Canvas* canvas = new CL_Canvas (CL_Display::get_width (), CL_Display::get_height ());
    
    canvas->lock ();
    for (int y = 0; y < CL_Display::get_height (); ++y)
      for (int x = 0; x < CL_Display::get_width (); ++x)
	{
	  bool is_in = false;

	  for (std::list<Polygon>::iterator i = polygons.begin ();
	       i != polygons.end (); ++i)
	    {
	      is_in = is_in || i->is_in (x, y);
	    }

	  if (is_in)
	    canvas->draw_pixel (x, y, 1.0, 0.0, 0.0);
	  else
	    canvas->draw_pixel (x, y, 0.0, 1.0, 0.0);
	}
    canvas->unlock ();

    return CL_Surface (canvas, true);
  }

  virtual int main(int, char **)
  {
    try
      {
	// Set mode: 640x480 16 bpp
	CL_SetupCore::init();
	CL_SetupDisplay::init();
	CL_Display::set_videomode(640, 480, 16, false);

	bool finished = false;
	Polygon polygon;
	polygon.finished = finished;
	std::list<Polygon> polygons;
	CL_Surface colmap;

	// Loop until the user hits escape:
	while (CL_Keyboard::get_keycode(CL_KEY_ESCAPE) == false)
	  {
	    if (CL_Keyboard::get_keycode (CL_KEY_X))
	      {
		std::cout << "Colmap2 started..." << std::endl;
		colmap = create_colmap2 (polygon);
		
		while (CL_Keyboard::get_keycode (CL_KEY_X))
		  CL_System::keep_alive ();
		std::cout << "Colmap2 finished" << std::endl;
	      }

	    if (CL_Keyboard::get_keycode (CL_KEY_C))
	      {
		std::cout << "Colmap started..." << std::endl;
		colmap = create_colmap (polygons);
		
		while (CL_Keyboard::get_keycode (CL_KEY_C))
		  CL_System::keep_alive ();
		std::cout << "Colmap finished" << std::endl;
	      }
	    
	    if (!finished && CL_Mouse::left_pressed ())
	      {
		polygon.points.push_back (CL_Vector(CL_Mouse::get_x (), CL_Mouse::get_y ()));

		while (CL_Mouse::left_pressed ())
		  CL_System::keep_alive ();
	      }

	    if (CL_Mouse::right_pressed ())
	      {
		if (polygon.convex ())
		  std::cout << "Convex" << std::endl;
		else
		  std::cout << "Concave" << std::endl;

		polygons = polygon.tessellate ();
		if (finished)
		  {
		    polygon.points.clear ();
		    polygons.clear ();
		    colmap = CL_Surface ();
		  }

		finished = !finished;
		polygon.finished = finished;

		while (CL_Mouse::right_pressed ())
		  CL_System::keep_alive ();
	      }

	    if (finished)
	      {
		bool in = false;
		int x = CL_Mouse::get_x ();
		int y = CL_Mouse::get_y ();

		for (std::list<Polygon>::iterator i = polygons.begin ();
		     i != polygons.end (); ++i)
		  {
		    in = in || i->is_in (x, y);
		  }
		if (in) {
		  CL_Display::clear_display(0.0, 0.0, 0.4);
		} else {
		  CL_Display::clear_display(0.0, 0.4, 0.0);
		}
		if (colmap)
		  colmap.put_screen (0,0);
	      }
	    else
	      {
		CL_Display::clear_display();	    
	      }

	    if (!colmap)
	      {
		polygon.draw (false);
		for (std::list<Polygon>::iterator i = polygons.begin ();
		     i != polygons.end ();
		     ++i)
		  i->draw(true);
	      }

	    // Flip front and backbuffer. This makes the changes visible:
	    CL_Display::flip_display();
	    
	    // Update keyboard input and handle system events:
	    CL_System::keep_alive();
	  }

	CL_SetupDisplay::deinit();
	CL_SetupCore::deinit();
      }
    catch (CL_Error err)
      {
	std::cout << "Error occoured: " << err.message.c_str() << std::endl;
	return 1;
      }

    return 0;
  }
} app;
