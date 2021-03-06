

#ifndef _DR_APPLICATION_
#define _DR_APPLICATION_

#include <map>
#include <chrono>
#include <gtkmm.h>

#include "Midi.hpp"

#define DRUM_VID	0x1941
#define DRUM_PID	0x8021

/*!
minimum interval between two notes in order to avoid some false contacts
value in milliseconds
*/
#define DRUM_MIN_INTERVAL	15


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
				static std::map<unsigned int,unsigned int> id_drum;
				
				std::chrono::system_clock::time_point events[6];
				int instruments[6];
				
				Midi * midi;
				
				int selected;
				
				Glib::RefPtr<Gtk::Application> gApp;
				Glib::RefPtr<Gtk::Builder> glade;
				Gtk::ApplicationWindow * winDrum;
				Gtk::Image * imgDrum;
				
				Glib::RefPtr<Gdk::Pixbuf> schema_pixbuf;
				Glib::RefPtr<Gdk::Pixbuf> schema;
				Glib::RefPtr<Gdk::Pixbuf> schema_map;
				
				Gtk::ComboBox * combos[6];
				
				Glib::Thread * thread_usb;
				
				bool usb_found;
				bool quit_request;
				
				Application(int argc,char * argv []);
				~Application();
				
				void UpdateImage();
				
				bool OnClose(GdkEventAny* event);
				
				void OnComboChanged();
				
				bool OnComboEnter(GdkEventCrossing*event);
				bool OnComboLeave(GdkEventCrossing*event);
				
				void UsbThread();
				
				void Run();
			};
		}
	}
}


#endif
