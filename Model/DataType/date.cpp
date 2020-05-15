#include "date.h"
#include "formaterror.h"

#include <algorithm>
#include <regex>
#include <sstream>

const int Date::DAYS_OF_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() {
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    _year = 1900 + now->tm_year;
    _month = now->tm_mon + 1;
    _day = now->tm_mday;
}

Date::Date(const QDate& qd) :
    _year(qd.year()), _month(qd.month()), _day(qd.day()){}

Date::Date(unsigned short day, unsigned short month, unsigned short year)
    : _year(year), _month(month), _day(day) {

    if(month == 0 || month > 12)
        throw std::invalid_argument("Month must be between 1 and 12");

    if(day == 0 || day > daysInMonth(month, year))
        throw std::invalid_argument("Invalid day");
}

unsigned short Date::day() const {
    return _day;
}

unsigned short Date::dayOfWeek() const {
  static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  int year = _year - (_month < 3);
  unsigned short dow = (year + year/4 - year/100 + year/400 + t[_month-1] + _day) % 7;
  return dow != 0 ? dow : 7;
}

unsigned short Date::dayOfYear() const {
    unsigned short day = 0;

    // aggiungo i giorni di ogni _month passato
    for(unsigned short i = 0; i < _month-2; i++) {
        day += DAYS_OF_MONTH[i];
        if(i == 1 && isLeapYear(_year))
            day += 1;
    }

    // aggiungo i giorni del _month corrente
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
    std::string aux(format);

    aux = std::regex_replace(aux, std::regex("dd"),
            _day < 10 ? "0" + std::to_string(_day) : std::to_string(_day));
    aux = std::regex_replace(aux, std::regex("d"), std::to_string(_day));

    aux = std::regex_replace(aux, std::regex("mm"),
            _month < 10 ? "0" + std::to_string(_month) : std::to_string(_month));
    aux = std::regex_replace(aux, std::regex("m"), std::to_string(_month));

    aux = std::regex_replace(aux, std::regex("yyyy"), std::to_string(_year));
    aux = std::regex_replace(aux, std::regex("yy"), std::to_string(_year % 100));

    return aux;
}

bool Date::operator==(const Date& d) const {
    return d._year == _year && d._month == _month && d._day == _day;
}

bool Date::operator!=(const Date& d) const {
    return d._year != _year || d._month != _month || d._day != _day;
}

bool Date::operator<(const Date& d) const {
    if (operator==(d)) return false;
    if (_year > d._year) return false;
    if (_year < d._year) return true;
    if (_month > d._month) return false;
    if (_month < d._month) return true;
    return _day < d._day;
}

bool Date::operator<=(const Date& d) const {
    return !operator>(d);
}

bool Date::operator>(const Date& d) const {
    return !operator==(d) && !operator<(d);
}

bool Date::operator>=(const Date& d) const {
    return !operator<(d);
}


bool Date::isLeapYear(unsigned short year) {
    // Se un _year è multiplo di 400, allora è bisestile
    if (year % 400 == 0)
        return true;

    // Se un _year è multiplo di 100, allora non è bisestile
    if (year % 100 == 0)
        return false;

    // Se l'_year è multiplo di 4, allora è bisestile
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

std::istream& operator>>(std::istream& in, Date& d) {
    std::string value;
    in >> value;

    unsigned int day, month, year;

    std::size_t pos_d = value.find('/');
    if(pos_d == std::string::npos)
        throw FormatError("Input must be in the form day/month/year");
    std::istringstream (value.substr(0, pos_d)) >> day;
    value = value.substr(pos_d+1);

    std::size_t pos_m = value.find('/');
    if(pos_m == std::string::npos)
        throw FormatError("Input must be in the form day/month/year");
    std::istringstream (value.substr(0, pos_m)) >> month;
    value = value.substr(pos_m+1);

    std::istringstream (value) >> year;
    d = Date(day, month, year);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Date& d) {
    return out << d.toString();
}
