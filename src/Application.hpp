

#ifndef _DR_APPLICATION_
#define _DR_APPLICATION_

#include <map>
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
				
				static std::map<int,std::string> mididrum;
				
				Glib::RefPtr<Gtk::Builder> glade;
				Gtk::ApplicationWindow * winDrum;
				Gtk::Image * imgDrum;
				
				Glib::RefPtr<Gdk::Pixbuf> schema;
				Glib::RefPtr<Gdk::Pixbuf> schema_map;
				
				Gtk::ComboBox * combos[6];
				
				Application();
				~Application();
				
				bool OnClose(GdkEventAny* event);
			};
		}
	}
}


#endif
