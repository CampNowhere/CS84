#include <stdint.h>
#include "channel.h"
#ifndef CS80_H
#define CS80_H

class CS80 {
    Channel channels[2];

    uint32_t sample_rate;

public:
    CS80();
    void set_sample_rate(uint32_t);
    void set_note_on(uint8_t);
    void set_note_off(uint8_t);
    void cycle();
    float sample();


private:
    float timer;
};

#endif // CS80_H
