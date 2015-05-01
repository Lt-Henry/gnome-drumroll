

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
	
	for(int n=0;n<6;n++)
	{
		combos[n]->pack_start(m_col_name);
		combos[n]->set_model(store);	
	}
	
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
