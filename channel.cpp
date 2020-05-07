#include "channel.h"
#include <stdio.h>

Channel::Channel() {
    saw = false;
    pulse = false;
    sine_level = 0.0;
}

Channel::~Channel(){

}

void Channel::set_sample_rate(uint32_t rate) {
    sample_rate = rate;
    uint8_t i;
    for(i = 0; i < OSC_COUNT; i++) {
        oscillators[i].set_sample_rate(sample_rate);
    }
}

void Channel::note_on(uint8_t note, uint8_t vel) {
    uint8_t i;
    for(i = 0; i < OSC_COUNT; i++) {
        if(!oscillators[i].gate) {
            oscillators[i].gate = true;
            oscillators[i].note_id = note;
            oscillators[i].set_frequency(midi_note_freqs[note]);
            return;
        }
    }
}

void Channel::note_off(uint8_t note, uint8_t vel){
    uint8_t i;
    for(i = 0; i < OSC_COUNT; i++) {
        if(oscillators[i].note_id == note) {
            oscillators[i].gate = false;
        }
    }
}

float Channel::sample() {
    float s = 0.0;
    uint8_t i;
    for(i = 0; i < OSC_COUNT; i++) {
        if(oscillators[i].gate) {
            oscillators[i].cycle();


            if(pulse){
                s += oscillators[i].pulse_amplitude;
            }
            if(saw){
                s += oscillators[i].saw_amplitude;
            }
            s = (float) filter.process(s);
            if(sine_level > 0.0){
                s += oscillators[i].sine_amplitude * sine_level;
            }

        }
    }
    return s;
}

void Channel::setSaw(bool s){
    printf("Saw to %d\n", s);
    saw = s;
}

void Channel::setPulse(bool s){
    printf("Pulse to %d\n", s);
    pulse = s;
}

void Channel::setSineLevel(int v){
    sine_level = (double) v / 100.0;
}

void Channel::setPulseWidth(int p){
    uint8_t i;
    for(i = 0; i < OSC_COUNT; i++) {
        oscillators[i].pulse_width_duty_cycle = p / 100.0;
    }
}

void Channel::setFilterCutoff(int c){
    filter.setCutoff(c / 100.0);
}

void Channel::setFilterResonance(int r){
    filter.setResonance((double)r / 100.0);
}
