#include <stdint.h>
#include "adsr.h"
#ifndef OSCILLATOR_H
#define OSCILLATOR_H
class Oscillator {
    double frequency;
    double period;
    double sample_period;
    double clock;
    double pulse_width_duty_cycle;

public:
    Oscillator();
    double sample_sine();
    double sample_pulse();
    double sample_saw();
    double sample_inverse_saw();
    void set_sample_rate(uint32_t);
    void set_frequency(double);
    void set_pulse_width(double);
    void cycle();
};

#endif // OSCILLATOR_H
