

#ifndef _DR_APPLICATION_
#define _DR_APPLICATION_

#include <map>
#include <gtkmm.h>

#define DRUM_VID	0x1941
#define DRUM_PID	0x8021


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
				static std::map<unsigned int,unsigned int> colormap;
				
				int selected;
				
				Glib::RefPtr<Gtk::Builder> glade;
				Gtk::ApplicationWindow * winDrum;
				Gtk::Image * imgDrum;
				
				Glib::RefPtr<Gdk::Pixbuf> schema_pixbuf;
				Glib::RefPtr<Gdk::Pixbuf> schema;
				Glib::RefPtr<Gdk::Pixbuf> schema_map;
				
				Gtk::ComboBox * combos[6];
				
				Glib::Thread * t_core;
				
				bool usb_found;
				bool quit_request;
				
				Application();
				~Application();
				
				void UpdateImage();
				
				bool OnClose(GdkEventAny* event);
				
				void OnComboChanged();
				
				bool OnComboEnter(GdkEventCrossing*event);
				bool OnComboLeave(GdkEventCrossing*event);
				
				void Run();
			};
		}
	}
}


#endif
