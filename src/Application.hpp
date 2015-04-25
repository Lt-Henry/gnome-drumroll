

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
				
				Application();
				~Application();
			};
		}
	}
}


#endif
