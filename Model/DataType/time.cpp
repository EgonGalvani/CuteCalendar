#include "time.h"

#include "formaterror.h"

#include <ctime>
#include <regex>
#include <string>
#include <sstream>
#include <stdexcept>

unsigned int Time::SECONDS_IN_DAY = 86400;

Time::Time() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    _sec = now->tm_sec + now->tm_min * 60 + now->tm_hour * 3600;
}

Time::Time(unsigned short hours, unsigned short minutes, unsigned short seconds)
    : _sec(hours*3600 + minutes*60 + seconds) {

    if(hours > 23)
        throw std::invalid_argument("Hours must be between 0 and 23");

    if(minutes > 59)
        throw std::invalid_argument("Minutes must be between 0 and 59");

    if(seconds > 59)
        throw std::invalid_argument("Seconds must be between 0 and 59");
}

void Time::addHours(unsigned int hours) {
    _sec = (_sec + hours*3600) % SECONDS_IN_DAY;
}

void Time::addMinutes(unsigned int minutes) {
     _sec = (_sec + minutes*60) % SECONDS_IN_DAY;
}

void Time::addSeconds(unsigned int seconds) {
     _sec = (_sec + seconds) % SECONDS_IN_DAY;
}

unsigned int Time::secSinceStartOfDay() const {
    return _sec;
}

unsigned short Time::hour() const {
    return _sec / 3600;
}

unsigned short Time::minute() const {
    return (_sec % 3600) / 60;
}
unsigned short Time::second() const {
    return _sec % 60;
}

/*
    h	The hour without a leading zero (0 to 23 or 1 to 12 if AM/PM display)
    hh	The hour with a leading zero (00 to 23 or 01 to 12 if AM/PM display)
    m	The minute without a leading zero (0 to 59)
    mm	The minute with a leading zero (00 to 59)
    s	The whole second, without any leading zero (0 to 59)
    ss	The whole second, with a leading zero where applicable (00 to 59)
*/
std::string Time::toString(const std::string& format) const {
    std::string aux(format);

    unsigned int hours = hour();
    unsigned int minutes = minute();
    unsigned int seconds = second();

    aux = std::regex_replace(aux, std::regex("hh"),
            hours < 10 ? "0" + std::to_string(hours) : std::to_string(hours));
    aux = std::regex_replace(aux, std::regex("h"), std::to_string(hours));

    aux = std::regex_replace(aux, std::regex("mm"),
            minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes));
    aux = std::regex_replace(aux, std::regex("m"), std::to_string(minutes));

    aux = std::regex_replace(aux, std::regex("ss"),
            seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds));
    aux = std::regex_replace(aux, std::regex("s"), std::to_string(seconds));

    return aux;
}

bool Time::operator==(const Time& t) const {
    return _sec == t._sec;
}

bool Time::operator!=(const Time& t) const {
    return _sec != t._sec;
}

bool Time::operator<(const Time& t) const {
    return _sec < t._sec;
}

bool Time::operator<=(const Time& t) const {
    return _sec <= t._sec;
}

bool Time::operator>(const Time& t) const {
    return _sec > t._sec;
}

bool Time::operator>=(const Time& t) const {
    return _sec >= t._sec;
}

Time Time::operator+(const Time& t) const {
    Time aux;
    aux._sec = (_sec + t._sec) % SECONDS_IN_DAY;
    return aux;
}

Time Time::operator-(const Time& t) const {
    Time aux;
    aux._sec = (_sec >= t._sec)
            ? _sec - t._sec
            : SECONDS_IN_DAY - (t._sec - _sec);
    return aux;
}

std::ostream& operator<<(std::ostream& out, const Time& t) {
    return out << t.toString();
}

std::istream& operator>>(std::istream& in, Time& t) {
    std::string value;
    in >> value;

    unsigned int hours, minutes, seconds;

    std::size_t pos_h = value.find(':');
    if(pos_h == std::string::npos)
        throw FormatError("Input must be in the form hours:minutes:seconds");
    std::istringstream (value.substr(0, pos_h)) >> hours;
    value = value.substr(pos_h+1);

    std::size_t pos_m = value.find(':');
    if(pos_m == std::string::npos)
        throw FormatError("Input must be in the form hours:minutes:seconds");
    std::istringstream (value.substr(0, pos_m)) >> minutes;
    value = value.substr(pos_m+1);

    std::istringstream (value) >> seconds;
    t = Time(hours, minutes, seconds);

    return in;
}
