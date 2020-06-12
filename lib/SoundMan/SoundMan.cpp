#include <Arduino.h>
#include <SoundMan.h>

void SoundMan::init(SoftwareSerial *sfSerial, uint32_t baudrate, uint32_t volume)
{
    m_sfSerial = sfSerial;
    m_baudrate = baudrate;
    m_vol = volume;

    m_sfSerial->begin(m_baudrate);
    mp3_set_serial(*m_sfSerial);
    mp3_set_volume(m_vol);
}

void SoundMan::playSound(uint8_t soundState)
{
    m_soundState = soundState;
    mp3_play(m_soundState);
}

void SoundMan::handler()
{

}