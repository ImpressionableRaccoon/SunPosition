#include "SunPosition.h"

SunPosition::SunPosition() {};

SunPosition::SunPosition(int year, int month, int day, int hour, int minute, int second, float latitude, float longitude) {
    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _minute = minute;
    _second = second;
    _latitude = latitude * DEG_TO_RAD;
    _longitude = longitude * DEG_TO_RAD;

    calculate();
}

void SunPosition::calculate() {
    float T, JD_frac, L0, M, e, C, L_true, f, R, GrHrAngle, Obl, RA, Decl, HrAngle;
    long JD_whole, JDx;

    if (_month <= 2) {
        _year--;
        _month += 12;
    }
    JD_whole = (long)(365.25 * (_year + 4716)) + (int)(30.6001 * (_month + 1)) + _day + 2 - _year / 100 + _year / 100 / 4 - 1524;
    JD_frac = (_hour + _minute / 60. + _second / 3600.) / 24. - .5;
    T = JD_whole - 2451545; T = (T + JD_frac) / 36525.;
    L0 = DEG_TO_RAD * fmod(280.46645 + 36000.76983 * T, 360);
    M = DEG_TO_RAD * fmod(357.5291 + 35999.0503 * T, 360);
    e = 0.016708617 - 0.000042037 * T;
    C = DEG_TO_RAD * ((1.9146 - 0.004847 * T) * sin(M) + (0.019993 - 0.000101 * T) * sin(2 * M) + 0.00029 * sin(3 * M));
    f = M + C;
    Obl = DEG_TO_RAD * (23 + 26 / 60. + 21.448 / 3600. - 46.815 / 3600 * T);
    JDx = JD_whole - 2451545;
    GrHrAngle = 280.46061837 + (360 * JDx) % 360 + .98564736629 * JDx + 360.98564736629 * JD_frac;
    GrHrAngle = fmod(GrHrAngle, 360.);
    L_true = fmod(C + L0, 6.28318531);
    R = 1.000001018 * (1 - e * e) / (1 + e * cos(f));
    RA = atan2(sin(L_true) * cos(Obl), cos(L_true));
    Decl = asin(sin(Obl) * sin(L_true));
    HrAngle = DEG_TO_RAD * GrHrAngle + _longitude - RA;
    elevation = asin(sin(_latitude) * sin(Decl) + cos(_latitude) * (cos(Decl) * cos(HrAngle))) / DEG_TO_RAD;
    azimuth = (PI + atan2(sin(HrAngle), cos(HrAngle) * sin(_latitude) - tan(Decl) * cos(_latitude))) / DEG_TO_RAD;
}