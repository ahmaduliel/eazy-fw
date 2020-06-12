#ifndef FLOWSTATE_H
#define FLOWSTATE_H
#include <LiquidCrystal.h>
#include <SoundMan.h>
#include <UVLight.h>

#define STATE_IDLE 0
#define STATE_PRE_EXPOSURE 1
#define STATE_UV_EXPLOSURE 2
#define STATE_FINISH_EXPLOSURE 3

#define SOUND_WELCOME 0
#define SOUND_STAND_OF 1
#define SOUND_STERILIZATION 2
#define SOUND_FINISH 3
#define SOUND_THANK_YOU 4

class FlowState
{
    public:
        void init(LiquidCrystal *lcd, uint16_t refreshRate, SoundMan *sound, UVLight *light, uint8_t dosisTimeMs);
        void display();
        bool isMotionDetected();
        bool isUVOn();
        unsigned long calculateToHours(unsigned long timeSec);
        void getLifeTime();
        void handler();
        unsigned long m_lifeTimeSec;
        unsigned long m_lifeTimeMinutes;
        unsigned long m_lifeTimeHours;
    private:
        void calculateExplosureTime(unsigned long startExplosure, uint8_t dosisTimeMs);
        LiquidCrystal *m_lcd;
        SoundMan *m_sound;
        UVLight *m_light;
        uint16_t m_refreshRateMs;
        unsigned long m_lastRefresh;
        bool m_UVState;
        bool m_lastUVState;
        unsigned long m_lastLifeTime;
        uint8_t m_dosisTimeMs;
        unsigned long m_startExplosure;
        unsigned long m_stopExplosure;
        unsigned long m_lastDosisTime;
        uint8_t m_currentFlowState;
        uint8_t m_lastFlowState;
};

#endif