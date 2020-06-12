#ifndef UVLIGHT_H
#define UVLIGHT_H

class UVLight{
    public:
        void init(uint8_t pin, bool inverted);
        void enable();
        void disable();
        void handler();
    private:
        bool m_enabled;
        bool m_inverted;
        uint8_t m_pin;
        bool m_state;
};

#endif