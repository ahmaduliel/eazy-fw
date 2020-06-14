#include <Arduino.h>
#include <FlowState.h>
#include <EEPROM.h>

void FlowState::init(LiquidCrystal *lcd, uint16_t refreshRate, SoundMan *sound, UVLight *light, uint16_t dosisTimeMs, uint8_t pinMotion)
{
    m_lcd = lcd;
    m_sound = sound;
    m_light = light;
    m_refreshRateMs = refreshRate;
    m_dosisTimeMs = dosisTimeMs;
    m_lastFlowState = 10;
    m_lastStatusMp3 = true;
    m_pinMotion = pinMotion;
    pinMode(m_pinMotion,INPUT);
    EEPROM.get(0,lifeTimeSaved);
    Serial.println("Get Life Time");
    Serial.println(lifeTimeSaved);
    // resetEeprom();
}

void FlowState::resetEeprom()
{
    for(int i=0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0);
    }
}

void FlowState::isMotionDetected()
{
    isMotionDetect = digitalRead(m_pinMotion);
    if (m_currentFlowState == STATE_IDLE && isMotionDetect == true)
    {
        m_currentFlowState = STATE_MOTION_DETECTED;
    }
}

bool FlowState::isUVOn()
{
    if(m_currentFlowState == STATE_UV_EXPLOSURE)
    {
        return true;
    }
    return false;
}

float FlowState::calculateToHours(float timeSec)
{
    float timeHours;
    timeHours = timeSec/3600;
    return timeHours;
}

float FlowState::calculateToMinutes(float timeSec)
{
    float timeMinutes;
    timeMinutes = timeSec/60;
    return timeMinutes;
}

void FlowState::calculateLifeTime()
{
    m_countLifeTime = m_stopExplosure - m_startExplosure;
    m_lifeTimeSec = (m_countLifeTime/1000);
}

void FlowState::calculateExplosureTime(unsigned long startExplosure, uint16_t dosisTimeMs)
{
    m_startExplosure = startExplosure;
    m_dosisTimeMs = dosisTimeMs;
    m_stopExplosure = m_startExplosure + m_dosisTimeMs;
    // Serial.println(m_startExplosure);
    // Serial.println(m_stopExplosure);
}

void FlowState::handler()
{
    if (m_currentFlowState == STATE_UV_EXPLOSURE)
    {
        if(millis() > m_stopExplosure)
        {
            if (m_currentFlowState == STATE_UV_EXPLOSURE)
            {
                m_light->disable();
                Serial.println("Dosis time done");
                m_currentFlowState = STATE_FINISH_EXPLOSURE;
                calculateLifeTime();
                lifeTimeSaved += calculateToMinutes(m_lifeTimeSec);
                Serial.println(lifeTimeSaved,4);
                EEPROM.put(0, lifeTimeSaved);
                Serial.println("Life Time Saved");
                // Serial.println(m_lifeTimeMs);
                // Serial.println(m_lifeTimeSec);
            }
        }
    }
    isMotionDetected();
    m_currentStatusMp3 = m_sound->getStatus();
    if (m_lastStatusMp3 == false && m_currentStatusMp3 == true)
    {
        switch(m_currentFlowState)
        {
            case STATE_MOTION_DETECTED:
            {
                m_currentFlowState = STATE_PRE_EXPOSURE;
                break;
            }
            case STATE_PRE_EXPOSURE:
            {
                m_currentFlowState = STATE_UV_EXPLOSURE;
                break;
            }
            case STATE_FINISH_EXPLOSURE:
            {
                m_currentFlowState = STATE_IDLE;
                break;
            }
        }
    }
    if(m_lastFlowState != m_currentFlowState)
    {
        m_lastFlowState = m_currentFlowState;
        switch(m_currentFlowState)
        {
            case STATE_IDLE:
            {
                Serial.println("Idle State");
                Serial.println("Idle waiting motion detection");
                break;
            }
            case STATE_MOTION_DETECTED:
            {
                Serial.println("Motion Detected");
                m_sound->playSound(SOUND_WELCOME);
                break;
            }
            case STATE_PRE_EXPOSURE:
            {
                Serial.println("Pre Explosure State");
                m_sound->playSound(SOUND_STAND_OF);
                break;
            }
            case STATE_UV_EXPLOSURE:
            {
                Serial.println("UV Explosure");
                m_sound->playSound(SOUND_STERILIZATION);
                calculateExplosureTime(millis(), m_dosisTimeMs);
                m_light->enable();
                Serial.println("Counting down...");
                break;
            }
            case STATE_FINISH_EXPLOSURE:
            {
                Serial.println("Finish Explosure");
                m_sound->playSound(SOUND_THANK_YOU);
                break;
            }
        }
    }
    m_lastStatusMp3 = m_currentStatusMp3;
}