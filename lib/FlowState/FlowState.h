#ifndef FLOWSTATE_H
#define FLOWSTATE_H
#include <LiquidCrystal.h>
#include <SoundMan.h>
#include <UVLight.h>

#define STATE_IDLE 0
#define STATE_MOTION_DETECTED 1
#define STATE_PRE_EXPOSURE 2
#define STATE_UV_EXPLOSURE 3
#define STATE_FINISH_EXPLOSURE 4

#define SOUND_WELCOME 0001
#define SOUND_STAND_OF 0002
#define SOUND_STERILIZATION 0003
#define SOUND_FINISH 0004
#define SOUND_THANK_YOU 0005

class FlowState
{
    public:
        void init(LiquidCrystal *lcd, uint16_t refreshRate, SoundMan *sound, UVLight *light, uint16_t dosisTimeMs, uint8_t pinMotion);
        void display();
        void isMotionDetected();
        bool isUVOn();
        float calculateToHours(float timeSec);
        float calculateToMinutes(float timeSec);
        void calculateLifeTime();
        void handler();
        void resetEeprom();
        float m_lifeTimeSec;
        float m_lifeTimeMinutes;
        float m_lifeTimeHours;
        float lifeTimeSaved;
    private:
        void calculateExplosureTime(unsigned long startExplosure, uint16_t dosisTimeMs);
        LiquidCrystal *m_lcd;
        SoundMan *m_sound;
        UVLight *m_light;
        uint16_t m_refreshRateMs;
        unsigned long m_lastRefresh;
        bool m_UVState;
        bool m_lastUVState;
        unsigned long m_countLifeTime;
        float currentLifeTime;
        uint16_t m_dosisTimeMs;
        unsigned long m_startExplosure;
        unsigned long m_stopExplosure;
        unsigned long m_lastDosisTime;
        uint8_t m_currentFlowState;
        uint8_t m_lastFlowState;
        bool m_lastStatusMp3;
        bool m_currentStatusMp3;
        bool isMotionDetect;
        uint8_t m_pinMotion;
};

#endif