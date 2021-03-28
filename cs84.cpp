#include "cs84.h"
CS84::CS84() {

}

CS84::~CS84() {

}

void CS84::set_sample_rate(uint32_t rate) {
    sample_rate = rate;
    channels[0].set_sample_rate(sample_rate);
    channels[1].set_sample_rate(sample_rate);
}
