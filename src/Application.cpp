

#include "Application.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace com::toxiclabs::drumroll;



Application::Application()
{



	glade=Gtk::Builder::create_from_resource("/com/toxiclabs/drumroll/gnome-drumroll.ui");

	

	glade->get_widget("winDrum",winDrum);

	winDrum->signal_delete_event().connect(
sigc::mem_fun(*this,&Application::OnClose));


	schema=Gdk::Pixbuf::create_from_resource(
"/com/toxiclabs/drumroll/schema.svg",320,240);

	glade->get_widget("imgDrum",imgDrum);
	imgDrum->set(schema);
	
	winDrum->show_all();
}


Application::~Application()
{
}

bool Application::OnClose(GdkEventAny* event)
{
	Gtk::Main::quit();
	
	return true;
}
