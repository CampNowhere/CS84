#include "oscillator.h"
#include <math.h>

Oscillator::Oscillator() {
    set_frequency(440);
    clock = 0;
    gate = false;
    voice_gain = 0.125;
    pulse_width_duty_cycle = 0.5;
}
void Oscillator::set_sample_rate(uint32_t rate) {
    sample_rate = rate;
    sample_period = 1.0 / (double) rate;
}

void Oscillator::cycle() {
    clock += sample_period;
    update_sine(clock);
    update_pulse(clock);
    update_saw(clock);
}

void Oscillator::set_frequency(double f) {
    frequency = f;
    period = 1.0 / f;
}

void Oscillator::update_sine(double t){
    sine_amplitude = std::sin(2 * M_PI * frequency * t) * voice_gain;
}

void Oscillator::update_pulse(double t){
    //pulse_amplitude = std::sin(2 * M_PI * frequency * t);
    //pulse_amplitude = (pulse_amplitude < 0) ? voice_gain : -(voice_gain);
    pulse_amplitude = saw_amplitude - phased_saw_amplitude;
}

void Oscillator::update_saw(double t){
    saw_amplitude = -(2.0 / M_PI) * std::atan(1.0/std::tan((M_PI * t) / period)) * voice_gain;
    phased_saw_amplitude = -(2.0 / M_PI) * std::atan(1.0/std::tan(((M_PI * t) / period) + M_PI * pulse_width_duty_cycle)) * voice_gain;
}
