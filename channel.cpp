#include "channel.h"
#include <stdio.h>

Channel::Channel() {
    saw = false;
    pulse = false;
    sine_level = 0.0;
    detune = 0.0;
    high_pass_filter.setFilterMode(Filter::FILTER_MODE_HIGHPASS);
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
    double note_freq = midi_note_freqs[note];
    note_freq = detunedFreq(note_freq, detune);
    for(i = 0; i < OSC_COUNT; i++) {
        if(!oscillators[i].gate) {
            oscillators[i].gate = true;
            oscillators[i].note_id = note;
            oscillators[i].set_frequency(note_freq);
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
        oscillators[i].cycle();
    }
    for(i = 0; i < OSC_COUNT; i++) {
        if(oscillators[i].gate) {

            if(pulse){
                s += oscillators[i].pulse_amplitude;
            }
            if(saw){
                s += oscillators[i].saw_amplitude;
            }
            s = (float) high_pass_filter.process(s);
            s = (float) low_pass_filter.process(s);
            if(sine_level > 0.0f){
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
        oscillators[i].pulse_width_duty_cycle = p / 100.0f;
    }
}

void Channel::setLPFCutoff(int c){
    double cutoff = std::pow(c / 255.0, 2);
    if(cutoff > 0.998) cutoff = 0.999;
    low_pass_filter.setCutoff(cutoff);
}

void Channel::setLPFResonance(int r){
    double resonance = r / 100.0;
    if(resonance > 0.998) resonance = 0.999;
    low_pass_filter.setResonance(resonance);
}

void Channel::setHPFCutoff(int c){
    double cutoff = std::pow(c / 255.0, 2);
    if(cutoff > 0.998) cutoff = 0.999;
    high_pass_filter.setCutoff(cutoff);
}

void Channel::setHPFResonance(int r){
    double resonance = r / 100.0;
    if(resonance > 0.998) resonance = 0.999;
    high_pass_filter.setResonance(resonance);
}

void Channel::setDetune(int d) {
    char valstr[10];
    detune = float(d) / 100;
    sprintf(valstr, "%.02f", detune);
    emit detuneSet(QString(valstr));
}

double Channel::detunedFreq(double freq, double cents) {
    return freq * pow(2.0, (cents / 1200.0));
}
