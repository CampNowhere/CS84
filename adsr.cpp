#include "adsr.h"

ADSR::ADSR(float p)
{
    period = p;
    level = 0;
    next_level = 0;
    ph = phase_attack;
    cycle_complete = false;
}

void ADSR::setAttack(float a) {
    attack = a;
}

void ADSR::setDecay(float d) {
    decay = d;
}

void ADSR::setSustain(float s) {
    sustain = s;
}

void ADSR::setRelease(float r) {
    release = r;
}

float ADSR::sample() {
    if(cycle_complete) {
        return 0;
    }
    level = next_level;
    switch(ph){
    case phase_attack:
        next_level += attack_delta;
        if(next_level > 1) {
            next_level = 1;
            ph = phase_decay;
        }
        break;
    case phase_decay:
        next_level -= decay_delta;
        if(next_level < sustain) {
            next_level = sustain;
            ph = phase_sustain;
        }
        break;
    case phase_sustain:
        next_level = level;
        break;
    case phase_release:
        next_level -= release_delta;
        if(next_level < 0) {
            cycle_complete = true;
            next_level = 0;
        }
        break;
    }
    return level;
}

void ADSR::gate() {
    attack_delta = (1 / attack) * period;
    decay_delta = (1 / decay) * period;
}

void ADSR::cutoff() {
    release_delta = (1 / release) * period;
    ph = phase_release;
}

bool ADSR::isSustain() {
    return ph == phase_sustain;
}

bool ADSR::isAttack() {
    return ph == phase_attack;
}

bool ADSR::isDecay() {
    return ph == phase_decay;
}

bool ADSR::isRelease() {
    return ph == phase_release;
}

bool ADSR::isCycleComplete() {
    return cycle_complete;
}

ADSR::~ADSR() {

}
