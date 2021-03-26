#ifndef ADSR_H
#define ADSR_H


class ADSR
{
    enum Phase { phase_attack, phase_decay, phase_sustain, phase_release };
    Phase ph;
    float level, next_level, period, attack, decay, sustain, release;
    float attack_delta, decay_delta, release_delta;
    bool cycle_complete;
public:
    ADSR(float period);
    ~ADSR();
    void gate();
    void cutoff();
    float sample();
    void setAttack(float a);
    void setDecay(float d);
    void setSustain(float s);
    void setRelease(float r);
    bool isSustain();
    bool isAttack();
    bool isDecay();
    bool isRelease();
    bool isCycleComplete();
};

#endif // ADSR_H
