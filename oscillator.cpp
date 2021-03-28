#include "oscillator.h"
#include <math.h>

Oscillator::Oscillator() {
    set_frequency(440);
    clock = 0;
    pulse_width_duty_cycle = 0.5;
}

void Oscillator::set_sample_rate(uint32_t rate) {
    sample_period = 1.0 / static_cast<double>(rate);
}

void Oscillator::cycle() {
    clock += sample_period;
}

void Oscillator::set_frequency(double f) {
    frequency = f;
    period = 1.0 / f;
}

double Oscillator::sample_sine(){
    return std::sin(2 * M_PI * frequency * clock);
}

double Oscillator::sample_pulse(){
    double phased_saw_amplitude = -(2.0 / M_PI) * std::atan(1.0/std::tan(((M_PI * clock) / period) + M_PI * pulse_width_duty_cycle));
    return sample_saw() - phased_saw_amplitude;
}

double Oscillator::sample_saw(){
    return -(2.0 / M_PI) * std::atan(1.0/std::tan((M_PI * clock) / period));

}

double Oscillator::sample_inverse_saw(){
    return (2.0 / M_PI) * std::atan(1.0/std::tan((M_PI * clock) / period));
}

void Oscillator::set_pulse_width(double p){
    if(p > 0.95) {
        pulse_width_duty_cycle = 0.95;
    } else if (p < 0.5) {
        pulse_width_duty_cycle = 0.5;
    } else {
        pulse_width_duty_cycle = p;
    }
}
