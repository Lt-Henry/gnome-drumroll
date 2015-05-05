

#include "Application.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace com::toxiclabs::drumroll;

map<int,string> Application::mididrum = {
	{35,"Acoustic Bass Drum"},
	{36,"Bass Drum 1"},
	{37,"Side Stick"},
	{38,"Acoustic Snare"},
	{39,"Hand Clap"},
	{40,"Electric Snare"},
	{41,"Low Floor Tom"},
	{42,"Closed Hi Hat"},
	{43,"High Floor Tom"},
	{44,"Pedal Hi Hat"},
	{45,"Low Tom"},
	{46,"Open Hi Hat"},
	{47,"Low-Mid Tom"},
	{48,"Hi-Mid Tom"},
	{49,"Crash Cymbal 1"},
	{50,"High Tom"},
	{51,"Ride Cymbal 1"},
	{52,"Chinese Cymbal"},
	{53,"Ride Bell"},
	{54,"Tambourine"},
	{55,"Splash Cymbal"},
	{56,"Cowbell"},
	{57,"Crash Cymbal 2"},
	{58,"Vibraslap"},
	{59,"Ride Cymbal 2"},
	{60,"Hi Bongo"},
	{61,"Low Bongo"},
	{62,"Mute Hi Conga"},
	{63,"Open Hi Conga"},
	{64,"Low Conga"},
	{65,"High Timbale"},
	{66,"Low Timbale"},
	{67,"High Agogo"},
	{68,"Low Agogo"},
	{69,"Cabasa"},
	{70,"Maracas"},
	{71,"Short Whistle"},
	{72,"Long Whistle"},
	{73,"Short Guiro"},
	{74,"Long Guiro"},
	{75,"Claves"},
	{76,"High Wood Block"},
	{77,"Low Wood Block"},
	{78,"Mute Cuica"},
	{79,"Open Cuica"},
	{80,"Mute Triangle"},
	{81,"Open Triangle"}
};

map<unsigned int,unsigned int> Application::colormap =
{

	{0,0xff9cbc1a},
	{1,0xff0fc4f1},
	{2,0xffdb9834},
	{3,0xff3c4ce7},
	{4,0xffb6599b},
	{5,0xffc7c3bd},
	
};


Application::Application()
{

	selected=-1;


	glade=Gtk::Builder::create_from_resource("/com/toxiclabs/drumroll/gnome-drumroll.ui");

	

	glade->get_widget("winDrum",winDrum);

	winDrum->signal_delete_event().connect(
sigc::mem_fun(*this,&Application::OnClose));


	schema=Gdk::Pixbuf::create_from_resource(
"/com/toxiclabs/drumroll/schema.svg",320,240);

	schema_map=Gdk::Pixbuf::create_from_resource(
"/com/toxiclabs/drumroll/schema-map.svg",320,240);

	schema_pixbuf=schema->copy();


	glade->get_widget("imgDrum",imgDrum);
	imgDrum->set(schema_pixbuf);
	
	
	glade->get_widget("combobox1",combos[0]);
	glade->get_widget("combobox2",combos[1]);
	glade->get_widget("combobox3",combos[2]);
	glade->get_widget("combobox4",combos[3]);
	glade->get_widget("combobox5",combos[4]);
	glade->get_widget("combobox6",combos[5]);
	
	Gtk::TreeModelColumn<int> m_col_id;
	Gtk::TreeModelColumn<string> m_col_name;
	
	Gtk::TreeModel::ColumnRecord columns;
	
	columns.add(m_col_id);
	columns.add(m_col_name);
	
	Glib::RefPtr<Gtk::ListStore> store = Gtk::ListStore::create(columns);
	
	
	for(pair<int,string> m : Application::mididrum)
	{
		Gtk::TreeModel::Row row;
		row=*(store->append());
		row.set_value(0,m.first);
		row.set_value(1,m.second);
	}
	
	winDrum->show_all();
	
	for(int n=0;n<6;n++)
	{
		combos[n]->pack_start(m_col_name);
		combos[n]->set_model(store);
		combos[n]->signal_changed().connect(sigc::mem_fun(*this,&Application::OnComboChanged));

		Gtk::Container * evbox = combos[n]->get_parent();
		evbox->signal_enter_notify_event().connect(sigc::mem_fun(*this,&Application::OnComboEnter));
		evbox->signal_leave_notify_event().connect(sigc::mem_fun(*this,&Application::OnComboLeave));
	}
	
	combos[0]->set_active(0);
	combos[1]->set_active(1);
	combos[2]->set_active(2);
	combos[3]->set_active(3);
	combos[4]->set_active(4);
	combos[5]->set_active(5);
	
	
}


Application::~Application()
{
}

void Application::UpdateImage()
{

	guint32 * buffer_schema;
	guint32 * buffer_schema_map;
	guint32 * buffer_schema_pixbuf;
	
	guint32 keycolor;
	
	buffer_schema = (guint32 *)schema->get_pixels();
	buffer_schema_map = (guint32 *)schema_map->get_pixels();
	buffer_schema_pixbuf = (guint32 *)schema_pixbuf->get_pixels();
	
	if(selected>=0)
		keycolor=Application::colormap[selected];
	else
		keycolor=0xdeadbeef;
	
	//cout<<"keycolor: "<<hex<<keycolor<<endl;
	
	for(int j=0;j<schema_pixbuf->get_height();j++)
	{
		for(int i=0;i<schema_pixbuf->get_width();i++)
		{
		
			if(buffer_schema_map[i+j*schema_pixbuf->get_width()]==keycolor)
			{
				buffer_schema_pixbuf[i+j*schema_pixbuf->get_width()]=0xff9cbc1a;
			}
			else
			{
				buffer_schema_pixbuf[i+j*schema_pixbuf->get_width()]=buffer_schema[i+j*schema_pixbuf->get_width()];
				
			}
			
			
			
			
			
		}
	}
	
	imgDrum->set(schema_pixbuf);
}

bool Application::OnClose(GdkEventAny* event)
{
	Gtk::Main::quit();
	
	return true;
}

void Application::OnComboChanged()
{
	Gtk::TreeModel::iterator iter;

	string name;
	int value;

	cout<<"**********************"<<endl;
	for(int n=0;n<6;n++)
	{
		iter = combos[n]->get_active();
		
		if(iter)
		{
			Gtk::TreeModel::Row row = *iter;
			row.get_value(1,name);
			row.get_value(0,value);
			
			cout<<"["<<n<<"] "<<name<<" "<<value<<endl;
		}
	}
	cout<<endl;
}

bool Application::OnComboEnter(GdkEventCrossing * event)
{
	
	for(int n=0;n<6;n++)
	{
		Glib::RefPtr<Gdk::Window> window = combos[n]->get_window();
		
		if(window->gobj()==event->window)
		{
			selected=n;
		}
	}
	
	UpdateImage();
	
	return false;
}

bool Application::OnComboLeave(GdkEventCrossing * event)
{
	selected=-1;
	
	UpdateImage();
	
	return false;
}
