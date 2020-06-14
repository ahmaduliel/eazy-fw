#include <Arduino.h>
#include <UVLight.h>

void UVLight::init(uint8_t pin, bool inverted)
{
    m_pin = pin;
    m_inverted = inverted;
    pinMode(m_pin, OUTPUT);
}

void UVLight::enable()
{
    m_enabled = true;
}

void UVLight::disable()
{
    m_enabled = false;
}

void UVLight::handler()
{
    if(m_inverted)
    {
        m_state = !m_enabled;
        
    }
    else
    {
        m_state = m_enabled;
    }
    digitalWrite(m_pin,m_state);
}