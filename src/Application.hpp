

#ifndef _DR_APPLICATION_
#define _DR_APPLICATION_

#include <gtkmm.h>

namespace com
{
	namespace toxiclabs
	{
		namespace drumroll
		{
			class Application
			{
				public:
				
				Glib::RefPtr<Gtk::Builder> glade;
				Gtk::ApplicationWindow * winDrum;
				Gtk::Image * imgDrum;
				
				Glib::RefPtr<Gdk::Pixbuf> schema;
				Glib::RefPtr<Gdk::Pixbuf> schema_map;
				
				Application();
				~Application();
				
				bool OnClose(GdkEventAny* event);
			};
		}
	}
}


#endif
