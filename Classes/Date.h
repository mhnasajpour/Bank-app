#ifndef __Date
#define __Date

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0);

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;
};

#endif