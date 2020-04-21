#ifndef TIME_H
#define TIME_H

#include <iostream>

class Time {
private:
    static unsigned int SECONDS_IN_DAY;
    unsigned int _sec;
public:
    Time(); // ora attuale
    Time(unsigned short, unsigned short, unsigned short = 0); // ore, minuti e secondi

    void addHours(unsigned int);
    void addMinutes(unsigned int);
    void addSeconds(unsigned int);

    unsigned short hour() const;
    unsigned short minute() const;
    unsigned short second() const;

    unsigned int secSinceStartOfDay() const;
    std::string toString(const std::string&) const;

    bool operator!=(const Time&) const;
    bool operator==(const Time&) const;
    bool operator<(const Time&) const;
    bool operator<=(const Time&) const;
    bool operator>(const Time&) const;
    bool operator>=(const Time&) const;

    Time operator+(const Time&) const;
    Time operator-(const Time&) const;
};

std::ostream& operator<<(std::ostream&, const Time&);
std::istream& operator>>(std::istream&, Time&);


#endif // TIME_H
