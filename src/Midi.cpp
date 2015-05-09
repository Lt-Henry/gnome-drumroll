/*
 Based on the work of Todd Kirby (ffmpeg.php@gmail.com) from alsamidi.c
*/

#include <iostream>
#include <stdexcept>

#include "Midi.hpp"


using namespace std;
using namespace com::toxiclabs::drumroll;


Midi::Midi(string name,string port_name)
{
	if (snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_OUTPUT, 0) != 0)
		throw runtime_error("Unable to open sequencer");
		
	if (snd_seq_set_client_name(seq_handle, name.c_str()) < 0)
	{
		Free();
		throw runtime_error("Unable to set client name");
	}
	
	seq_port = snd_seq_create_simple_port(seq_handle, port_name.c_str(), SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ, SND_SEQ_PORT_TYPE_MIDI_GENERIC);
	if (seq_port < 0)
	{
		Free();
		throw runtime_error("Unable to create sequencer port");
	}
}


Midi::~Midi()
{
	Free();
}


void Midi::Free()
{

	if (seq_handle != nullptr)
		snd_seq_close(seq_handle);

	if (seq_port > 0)
		snd_seq_delete_simple_port(seq_handle, seq_port);
}


void Midi::NoteOn(unsigned int note,int velocity,int channel)
{
	snd_seq_event_t ev;
	snd_seq_ev_clear(&ev);
	snd_seq_ev_set_source(&ev, seq_port);
	snd_seq_ev_set_subs(&ev);
	snd_seq_ev_set_direct(&ev);

	snd_seq_ev_set_note(&ev, channel-1, note, velocity, 0);
	ev.type = SND_SEQ_EVENT_NOTEON;

	if (snd_seq_event_output(seq_handle, &ev) < 0)
		throw runtime_error("Unable to send note-on event");

	snd_seq_drain_output(seq_handle);
}


void Midi::NoteOff(unsigned int note,int velocity,int channel)
{
	snd_seq_event_t ev;
	snd_seq_ev_clear(&ev);
	snd_seq_ev_set_source(&ev, seq_port);
	snd_seq_ev_set_subs(&ev);
	snd_seq_ev_set_direct(&ev);

	snd_seq_ev_set_note(&ev, channel-1, note, velocity, 0);
	ev.type = SND_SEQ_EVENT_NOTEOFF;

	if (snd_seq_event_output(seq_handle, &ev) < 0)
		throw runtime_error("Unable to send note-off event");

	snd_seq_drain_output(seq_handle);

}

