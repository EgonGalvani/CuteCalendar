#include "time.h"

#include <ctime>
#include <regex>
 #include <string>

unsigned int Time::_secondsInDay = 86400;

Time::Time() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    _sec = now->tm_sec + now->tm_min * 60 + now->tm_hour * 3600;
}

// da aggiungere eccezioni (se es. hours > 23)
Time::Time(unsigned int hours, unsigned int minutes, unsigned int seconds)
    : _sec(hours*3600 + minutes*60 + seconds) {}

void Time::addHours(unsigned int hours) {
    _sec = (_sec + hours*3600) % _secondsInDay;
}

void Time::addMinutes(unsigned int minutes) {
     _sec = (_sec + minutes*60) % _secondsInDay;
}

void Time::addSeconds(unsigned int seconds) {
     _sec = (_sec + seconds) % _secondsInDay;
}

unsigned int Time::secSinceStartOfDay() const {
    return _sec;
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

    unsigned int hours = _sec / 3600;
    unsigned int minutes = (_sec % 3600) / 60;
    unsigned int seconds = _sec - hours*3600 - minutes*60;

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

