#ifndef SUNPOSITION_H
#define SUNPOSITION_H

#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

class SunPosition
{
    public:
        SunPosition(int year, int month, int day, int hour, int minute, int second, float latitude, float longitude);
        float azimuth;
        float elevation;
    private:
        int _year, _month, _day, _hour, _minute, _second;
        float _latitude, _longitude;
        void calculate();
};

#endif