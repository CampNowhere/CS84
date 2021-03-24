#include <stdint.h>
#ifndef OSCILLATOR_H
#define OSCILLATOR_H
class Oscillator {
    double frequency;
    double period;
    double sample_period;
    double clock;
    float phased_saw_amplitude;
    uint32_t sample_rate;
    float voice_gain;
    void update_sine(double t);
    void update_pulse(double t);
    void update_saw(double t);
    void update_inverse_saw(double t);

    bool check_gate();

public:
    Oscillator();
    void set_frequency(double);
    void set_sample_rate(uint32_t);
    void set_pulse_width();
    void cycle();


    float sine_amplitude;
    float pulse_amplitude;
    float saw_amplitude;
    double inverse_saw_amplitude;

    float pulse_width_duty_cycle;
    bool gate;
    uint8_t note_id;
};

#endif // OSCILLATOR_H
