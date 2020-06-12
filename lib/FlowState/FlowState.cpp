#include <Arduino.h>
#include <FlowState.h>

void FlowState::init(LiquidCrystal *lcd, uint16_t refreshRate, SoundMan *sound, UVLight *light, uint8_t dosisTimeMs)
{
    m_lcd = lcd;
    m_sound = sound;
    m_light = light;
    m_refreshRateMs = refreshRate;
    m_dosisTimeMs = dosisTimeMs;
}

bool FlowState::isMotionDetected()
{

}

bool FlowState::isUVOn()
{

}

unsigned long FlowState::calculateToHours(unsigned long timeSec)
{
    unsigned long timeHours;
    timeHours = timeSec/3600;
    return timeHours;
}

void FlowState::getLifeTime()
{
    if((millis() - m_lastLifeTime) == 1000)
    {
        m_lifeTimeSec++;
        m_lifeTimeHours = calculateToHours(m_lifeTimeSec);
        m_lastLifeTime = millis();
    }
}

void FlowState::calculateExplosureTime(unsigned long startExplosure, uint8_t dosisTimeMs)
{
    m_startExplosure = startExplosure;
    m_dosisTimeMs = dosisTimeMs;
    m_stopExplosure = m_startExplosure + m_dosisTimeMs;
}

void FlowState::handler()
{
    if(millis() > m_stopExplosure)
    {

    }
    if(m_lastFlowState != m_currentFlowState)
    {
        switch(m_currentFlowState)
        {
            case STATE_IDLE:
            {
                Serial.println("Idle State");
                if(isMotionDetected())
                {
                    Serial.println("Motion Detected");
                    m_sound->playSound(SOUND_WELCOME);
                    m_currentFlowState = STATE_PRE_EXPOSURE;
                }
                else
                {
                    Serial.println("Idle waiting motion detection");
                    m_currentFlowState = STATE_IDLE;
                }
                break;
            }
            case STATE_PRE_EXPOSURE:
            {
                Serial.println("Pre Explosure State");
                m_sound->playSound(SOUND_STAND_OF);
                m_currentFlowState = STATE_UV_EXPLOSURE;
                break;
            }
            case STATE_UV_EXPLOSURE:
            {
                Serial.println("UV Explosure");
                calculateExplosureTime(millis(), m_dosisTimeMs);
                getLifeTime();
                m_sound->playSound(SOUND_STERILIZATION);
                break;
            }
            case STATE_FINISH_EXPLOSURE:
            {
                Serial.println("Finish Explosure");
                m_sound->playSound(SOUND_THANK_YOU);
                m_currentFlowState = STATE_IDLE;
                break;
            }
        }
    }
    
}