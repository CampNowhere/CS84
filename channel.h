#include <stdint.h>
#include <algorithm>
#include <QObject>
#include <math.h>
#include "voice.h"
#include "filter.h"
#ifndef CHANNEL_H
#define CHANNEL_H
#define VOICE_COUNT 8

class Channel{

    Voice voices[VOICE_COUNT];

    Filter low_pass_filter, high_pass_filter;

    bool saw;
    bool pulse;
    float pulse_width;
    float pulse_width_modulation;
    float pulse_width_modulation_speed;
    float sine_level;
    double * pitch_bend_cents;
    double detune;
    uint32_t sample_rate;
public:
    Channel();
    ~Channel();
    void set_sample_rate(uint32_t);
    void note_on(uint8_t note, uint8_t vel);
    void note_off(uint8_t note, uint8_t vel);
    float sample();
    void assignPitchBendCents(double * p);
    void setSaw(bool s);
    void setPulse(bool s);
    void setSineLevel(int v);
    void setPulseWidth(int p);
    void setLPFCutoff(int c);
    void setLPFResonance(int r);
    void setHPFCutoff(int c);
    void setHPFResonance(int r);
    void setDetune(double cents);

private:
    double detunedFreq(double freq, double cents);
};

#endif // CHANNEL_H
