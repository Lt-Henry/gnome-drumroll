

#include "Application.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace com::toxiclabs::drumroll;



Application::Application()
{

	vector<string>  children = Gio::Resource::enumerate_children_global("/com/toxiclabs/drumroll");

	for(string s : children)
	{
		cout<<s<<endl;
	}

	glade=Gtk::Builder::create_from_resource("/com/toxiclabs/drumroll/gnome-drumroll.ui");
	
}


Application::~Application()
{
}


