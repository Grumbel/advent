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
  
  Valid (bool arg_valid)
    : valid (arg_valid)
  {}

  bool is_valid () { return valid; }
  operator T () { return obj; }
  T& get () { return obj; }
};

Valid<CL_Vector> intersec (CL_Vector a1, CL_Vector a2,
			   CL_Vector b1, CL_Vector b2)
{
  CL_Vector a = a1;
  CL_Vector b = a2 - a1;

  CL_Vector c = b1;
  CL_Vector d = b2 - b1;

  double lambda;
  double mu;

  // The lines are parallel
  if ((b.y*d.x - b.x*d.y) == 0.0)
    {
      return Valid<CL_Vector>(CL_Vector (0.0, 0.0), false);
    }

  lambda = (c.y*d.x - c.x*d.y) + (a.x*d.y - a.y*d.x);
  lambda /= (b.y*d.x - b.x*d.y);

  if (d.x != 0.0)
    {
      mu = (a.x + (lambda * b.x) - c.x) / d.x;
    }
  else
    {
      mu = (a.y + (lambda * b.y) - c.y) / d.y;
    }

  CL_Vector col (a + b*lambda);
  
  if (lambda >= 0 && lambda <= 1.0
      && mu >= 0 && mu <= 1.0)
    return Valid<CL_Vector>(col, true);
  else
    return Valid<CL_Vector>(col, false);
}
    
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

	//bool finished = false;
	
	CL_Vector a1, a2;
	CL_Vector b1, b2;
	int count = 0;

	// Loop until the user hits escape:
	while (CL_Keyboard::get_keycode(CL_KEY_ESCAPE) == false)
	  {
	    if (CL_Mouse::left_pressed ())
	      {
		++count;

		if (count == 4)
		  {
		    std::cout << "Intersec" << std::endl;
		  }
		if (count == 5)
		  count = 0;

		while (CL_Mouse::left_pressed ())
		  CL_System::keep_alive ();
	      }

	    switch (count)
	      {
	      case 0:
		a1 = CL_Vector (CL_Mouse::get_x (), CL_Mouse::get_y ());
		break;
	      case 1:
		a2 = CL_Vector (CL_Mouse::get_x (), CL_Mouse::get_y ());
		break;
	      case 2:
		b1 = CL_Vector (CL_Mouse::get_x (), CL_Mouse::get_y ());
		break;
	      case 3:
		b2 = CL_Vector (CL_Mouse::get_x (), CL_Mouse::get_y ());
		break;
	      }

	    if (count > 0)
	      CL_Display::draw_line ((int)a1.x, (int)a1.y, (int)a2.x, (int)a2.y,
				     1.0, 1.0, 1.0);
	    
	    if (count > 2)
	      CL_Display::draw_line ((int)b1.x, (int)b1.y, (int)b2.x, (int)b2.y,
				     1.0, 1.0, 1.0);

	    if (count >= 3)
	      {
		Valid<CL_Vector> col (intersec (a1, a2, b1, b2));
		if (col.is_valid ())
		  {
		    CL_Display::fill_rect (col.get ().x - 5,
					   col.get ().y - 5,
					   col.get ().x + 5,
					   col.get ().y + 5,
					   1.0, 0.0, 0.0);
		  }
		else
		  {
		    CL_Display::fill_rect (col.get ().x - 5,
					   col.get ().y - 5,
					   col.get ().x + 5,
					   col.get ().y + 5,
					   0.0, 0.0, 1.0);
		  }
	      }

	    CL_Display::flip_display();

	    // Update keyboard input and handle system events:
	    CL_System::keep_alive();
	    CL_Display::clear_display ();    
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
