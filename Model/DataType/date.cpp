#include "date.h"

#include <algorithm>
#include <regex>
#include <sstream>

const int Date::DAYS_OF_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool Date::isLeapYear(unsigned short year) {
    // Se un anno è multiplo di 400, allora è bisestile
    if (year % 400 == 0)
        return true;

    // Se un anno è multiplo di 100, allora non è bisestile
    if (year % 100 == 0)
        return false;

    // Se l'anno è multiplo di 4, allora è bisestile
    if (year % 4 == 0)
        return true;
    return false;
}

unsigned short Date::daysInMonth(unsigned short month, unsigned short year) {
    if(month == 0 || month > 12)
        throw std::invalid_argument("Month must be between 1 and 12");

    return isLeapYear(year) && month == 2
        ? 29
        : DAYS_OF_MONTH[month-1];
}

Date::Date(unsigned short year, unsigned short month, unsigned short day)
    : _year(year), _month(month), _day(day) {

    if(month == 0 || month > 12)
        throw std::invalid_argument("Month must be between 1 and 12");

    if(day == 0 || day > daysInMonth(month, year))
        throw std::invalid_argument("Invalid day");

}

unsigned short Date::day() const {
    return _day;
}

unsigned short Date::dayOfWeek() const {} // todo

unsigned short Date::dayOfYear() const {
    unsigned short day = 0;

    // aggiungo i giorni di ogni mese passato
    for(unsigned short i = 0; i < _month-2; i++) {
        day += DAYS_OF_MONTH[i];
        if(i == 1 && isLeapYear(_year))
            day += 1;
    }

    // aggiungo i giorni del mese corrente
    day += _day;
    return day;
}

unsigned short Date::daysInMonth() const {
    return daysInMonth(_month, _year);
}

unsigned short Date::daysInYear() const {
    return isLeapYear(_year) ? 366 : 365;
}

unsigned short Date::month() const {
    return _month;
}

unsigned short Date::year() const {
    return _year;
}

/*
    d	The day as a number without a leading zero (1 to 31)
    dd	The day as a number with a leading zero (01 to 31)
    M	The month as a number without a leading zero (1 to 12)
    MM	The month as a number with a leading zero (01 to 12)
    yy	The year as a two digit number (00 to 99)
    yyyy The year as a four digit number. If the year is negative, a minus sign is prepended, making five characters.
*/
std::string Date::toString(const std::string& format) const {

}

bool Date::operator==(const Date& d) const {
    return d._year == _year && d._month == _month && d._day == _day;
}

bool Date::operator!=(const Date& d) const {
    return d._year != _year || d._month != _month || d._day != _day;
}

bool Date::operator<(const Date& d) const {
    return _year < d._year; // TODO
}

bool Date::operator<=(const Date& d) const {

}

bool Date::operator>(const Date& d) const {

}

bool Date::operator>=(const Date& d) const {

}

std::ostream& operator<< (std::ostream& out, const Date& d) {
    return out; // << d._day << "/" << d._month << "/" << d._year;
}
