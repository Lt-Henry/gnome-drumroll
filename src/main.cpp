
#include <gtkmm.h>


int main(int argc,char * argv[])
{
	Glib::RefPtr<Gtk::Aplication> app;
	
	app = Gtk::Application::create(argc,argv,"com.toxiclabs.drumroll");
	
	
	
	return 0;
}
