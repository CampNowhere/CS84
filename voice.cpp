#include "voice.h"

Voice::Voice()
{
    voice_gain = 0.1;
}

void Voice::set_sample_rate(uint32_t rate) {
    osc.set_sample_rate(rate);
}

void Voice::gate(uint8_t note) {

}

void Voice::assign_detune(double *d) {
    detune_cents = d;
}
