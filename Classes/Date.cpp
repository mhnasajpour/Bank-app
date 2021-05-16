#include "Date.h"

Date::Date(int _day, int _month, int _year)
{
    day = _day;
    month = _month;
    year = _year;
}

void Date::setDay(int _day)
{
    day = _day;
}

void Date::setMonth(int _month)
{
    month = _month;
}

void Date::setYear(int _year)
{
    year = _year;
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}