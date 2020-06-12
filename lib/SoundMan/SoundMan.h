#ifndef SOUNDMAN_H
#define SOUNDMAN_H
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>

class SoundMan
{
    public:
        void init(SoftwareSerial *sfSerial, uint32_t baudrate, uint32_t volume);
        void handler();
        void playSound(uint8_t soundState);
    private:
        SoftwareSerial *m_sfSerial;
        uint32_t m_baudrate;
        uint32_t m_vol;
        uint8_t m_soundState;
};

#endif