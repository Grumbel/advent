/*
	Init display example.
*/

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>

double two_pi = 6.283185307179586476925286766559005768394338798750211641949889184615632;

class Polygon
{
public:
  std::list<CL_Vector> points;
  bool finished;
  
  bool is_in (float x, float y) 
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
    
    double epsilon = 0.001;

    std::cout << "Angle: " << complete_angle << std::endl;

    if ((complete_angle < two_pi + epsilon) && (complete_angle > two_pi - epsilon))
      return true;
    else
      return false;
  }
  
  void draw ()
  {
    for (std::list<CL_Vector>::iterator i = points.begin ();
	 i != points.end (); ++i)
      {
	std::list<CL_Vector>::iterator next = i;
	++next;
	if (next == points.end ())
	  next = points.begin ();

	if (next == points.begin () && !finished)
	  CL_Display::draw_line (i->x, i->y, next->x, next->y,
				 1.0, 0.0, 0.0);
	else
	  CL_Display::draw_line (i->x, i->y, next->x, next->y,
				 1.0, 1.0, 1.0);

      }
  }
};

class InitDisplayApp : public CL_ClanApplication
{
public:
  virtual char *get_title() { return "InitDisplay application"; }

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

	// Loop until the user hits escape:
	while (CL_Keyboard::get_keycode(CL_KEY_ESCAPE) == false)
	  {
	    
	    if (!finished && CL_Mouse::left_pressed ())
	      {
		polygon.points.push_back (CL_Vector(CL_Mouse::get_x (), CL_Mouse::get_y ()));

		while (CL_Mouse::left_pressed ())
		  CL_System::keep_alive ();
	      }

	    if (CL_Mouse::right_pressed ())
	      {
		if (finished)
		  polygon.points.clear ();

		finished = !finished;
		polygon.finished = finished;

		while (CL_Mouse::right_pressed ())
		  CL_System::keep_alive ();
	      }

	    // Clear display with random colors
	    if (finished)
	      if (polygon.is_in (CL_Mouse::get_x (), CL_Mouse::get_y ()))
		CL_Display::clear_display(0.0, 0.0, 0.4);
	      else
		CL_Display::clear_display(0.0, 0.4, 0.0);
	    else
	      CL_Display::clear_display();	    

	    polygon.draw ();

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
