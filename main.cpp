#include "csjack.h"
#include "channel.h"
#include "oscillator.h"
#include <jack/jack.h>
#include <jack/midiport.h>
#include <stdio.h>
#include <QApplication>

Channel * ch;
jack_port_t * midiport;
jack_port_t * audioport;

void process_midi_event(void * buf){
    //jack_default_audio_sample_t
    uint32_t event_count = jack_midi_get_event_count(buf);
    jack_midi_event_t event;
    for(uint32_t i = 0; i < event_count; i++) {
        int ok = jack_midi_event_get(&event, buf, i);
        if(ok == 0) {
            uint8_t event_code = event.buffer[0] >> 4;
            switch (event_code) {
            case 8:
                ch->note_off(event.buffer[1], event.buffer[2]);
                break;
            case 9:
                ch->note_on(event.buffer[1], event.buffer[2]);
                break;
            default:
                break;
            }
        }
    }
}

int process(jack_nframes_t nframes, void * arg) {
    void * midibuffer = jack_port_get_buffer(midiport, nframes);
    float * audiobuffer = (float *) jack_port_get_buffer(audioport, nframes);
    if (midibuffer != NULL) {
        process_midi_event(midibuffer);
    }
    for(int i = 0; i < nframes; i++) {
        audiobuffer[i] = ch->sample();
    }
    return 0;
}

int main(int argc, char *argv[])
{
    jack_status_t jack_status;
    jack_client_t * client;
    client = jack_client_open(
        "SID",
        jack_options_t(JackNoStartServer | JackUseExactName ),
        &jack_status
    );
    if (jack_status & JackFailure) {
        printf("Unable to find jack server!\n");
        exit(-1);
    }
    jack_nframes_t sample_rate = jack_get_sample_rate(client);
    printf("Server operating at sample rate of %d\n", sample_rate);
    //jack_on_shutdown(client, shutdown, 0);
    jack_set_process_callback(client, process, 0);

    midiport = jack_port_register(
        client,
        "MIDI In",
        JACK_DEFAULT_MIDI_TYPE,
        JackPortIsInput,
        0
    );
    audioport = jack_port_register(
        client,
        "Mono Out",
        JACK_DEFAULT_AUDIO_TYPE,
        JackPortIsOutput,
        0
    );
    QApplication a(argc, argv);
    CSJack w;
    ch = new Channel;
    w.ConnectControls(ch, nullptr);
    ch->set_sample_rate(sample_rate);
    jack_activate(client);
    w.show();

    return a.exec();
}
