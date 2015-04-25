
#include "Application.hpp"

#include <gtkmm.h>

using namespace com::toxiclabs::drumroll;

int main(int argc,char * argv[])
{
	Gtk::Main kit(argc, argv);
	
	Application app;
	
	Gtk::Main::run();
	
	return 0;
}
