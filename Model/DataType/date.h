#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    unsigned short _day, _month, _year;
public:
    Date(); // data attuale
    Date(unsigned short, unsigned short, unsigned short); // anno, mese e giorno

    void addDays(unsigned short);
    void addMonths(unsigned short);
    void addYears(unsigned short);

    unsigned short day() const;
    unsigned short dayOfWeek() const;
    unsigned short dayOfYear() const;
    unsigned short daysInMonth() const;
    unsigned short daysInYear() const;

    unsigned short month() const;
    unsigned short year() const;

    unsigned int daysTo(const Date& d) const;

    unsigned short secSinceStartOfDay() const;
    std::string toString(const std::string&) const;

    bool operator!=(const Date&) const;
    bool operator==(const Date&) const;
    bool operator<(const Date&) const;
    bool operator<=(const Date&) const;
    bool operator>(const Date&) const;
    bool operator>=(const Date&) const;

    static Date currentDate();
    static Date fromString(const std::string&);
    static bool isLeapYear(unsigned short);
};

std::ostream& operator<<(std::ostream&, const Date&);
std::istream& operator>>(std::ostream&, Date&);

#endif // DATE_H
