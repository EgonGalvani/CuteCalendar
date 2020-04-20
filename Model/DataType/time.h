#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
private:
    static unsigned int _secondsInDay;
    unsigned int _sec;
public:
    Time(); // ora attuale
    Time(unsigned int, unsigned int, unsigned int = 0); // ore, minuti e secondi

    // Time(const Time&) coincide con quello standard

    void addHours(unsigned int);
    void addMinutes(unsigned int);
    void addSeconds(unsigned int);

    unsigned int hour() const;
    unsigned int minute() const;
    unsigned int second() const;

    unsigned int secSinceStartOfDay() const;
    std::string toString(const std::string&) const;

    bool operator!=(const Time&) const;
    bool operator==(const Time&) const;
    bool operator<(const Time&) const;
    bool operator<=(const Time&) const;
    bool operator>(const Time&) const;
    bool operator>=(const Time&) const;
};

std::ostream& operator<<(std::ostream&, const Time&);
std::istream& operator>>(std::istream&, Time&);


#endif // TIME_H
