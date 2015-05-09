
#ifndef _DR_MIDI_
#define _DR_MIDI_

#include <string>
#include <alsa/asoundlib.h>

namespace com
{
	namespace toxiclabs
	{
		namespace drumroll
		{
		
		
			enum Velocity
			{
				Min=0, Max=127
			};
			
			class Midi
			{
				private:
				
				snd_seq_t * seq_handle;
				int seq_port;
				
				public:
				
				/*!
					Creates an alsa midi connection
					/param name client name
					/param port_name port name
					
				*/
				Midi(std::string name,std::string port_name);

				/*!
					destructor
				*/
				~Midi();
				
				/*!
					Sends a Note On event
					/param note Note number
					/param velocity Note 'pressure', in the 0-127 range
					/param channel Midi channel, defaults to 10, reserved for percussion samples
				*/
				void NoteOn(unsigned int note,int velocity,int channel=10);
				void NoteOff(unsigned int note,int velocity,int channel=10);
				
				protected:
				
				/*!
				 Free alsa resources
				 */
				void Free();
			};
		}
	}
}


#endif

