#include "cs80.h"
CS80::CS80() {

}

void CS80::set_sample_rate(uint32_t rate) {
    sample_rate = rate;
    channels[0].set_sample_rate(sample_rate);
    channels[1].set_sample_rate(sample_rate);
}
