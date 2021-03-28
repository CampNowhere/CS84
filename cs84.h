#include <stdint.h>
#include <QObject>
#include "channel.h"
#ifndef CS84_H
#define CS84_H

class CS84 : public QObject {
    Q_OBJECT

    Channel channels[2];
public:
    CS84();
    ~CS84();
    void set_sample_rate(uint32_t);
    void set_note_on(uint8_t);
    void set_note_off(uint8_t);
    void cycle();
    float sample();


private:
    float timer;
    uint32_t sample_rate;
};

#endif // CS80_H
