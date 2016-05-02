#include "Date_interval.h"
//#include <iostream>
//using namespace std;

Date_interval::Date_interval(const int &dbegin, const int &dend)
: m_begin {dbegin}, m_end {dend}
{
    m_interval = calculate(dbegin, dend);//ctor
}

Date_interval::Date_interval()
{
    //ctor
}
int Date_interval::get_Interval()
{
    return m_interval;
}
//Check for leap year.
bool Date_interval::leap_y(const int &dYear)
{
    return (dYear % 4 == 0);
}
//Calculate sequence number of the day in year for the date in the yyyymmdd format.
int Date_interval::day_in_y(const int &yyyymmdd)
{
    int ord_year[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap_year[12] {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int nDays {0};
    if (leap_y(year(yyyymmdd)))
    {
        for (int i = 0; i < month(yyyymmdd) - 1; ++i)
             nDays += leap_year[i];
        return (nDays + day(yyyymmdd));
    }
    else
    {
        for (int i = 0; i < month(yyyymmdd) - 1; ++i)
            nDays += ord_year[i];
        return (nDays + day(yyyymmdd));
    }
}
int Date_interval::ordinal_to_d(const int &ordinal, const int &dyear)
{
    int ord_year[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap_year[12] {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ord_sum[12] {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int leap_sum[12] {31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
    if(ordinal > 366)
        return -1;
    else
    {
        if(ordinal > 365 && !leap_y(dyear))
            return -1;
        else
        {
            if(leap_y(dyear))
            {
                for(int i = 0; i < 12; ++i)
                {
                    if(ordinal < leap_sum[i])
                        return dyear * 10000 + (i + 1) * 100 + leap_year[i] - (leap_sum[i] - ordinal);
                }
            }
            else
            {
                for(int i = 0; i < 12; ++i)
                {
                    if(ordinal < ord_sum[i])
                        return dyear * 10000 + (i + 1) * 100 + ord_year[i] - (ord_sum[i] - ordinal);
                }
            }
        }
    }
}
//Calculate interval in days between two dates in yyyymmdd format.
int Date_interval::calculate(const int &dbegin, const int &dend)
{
    if (year(dbegin) == year(dend))
    {
        return (day_in_y(dend) - day_in_y(dbegin));
    }
    else
    {
        if (leap_y(year(dbegin)))
            return (366 - day_in_y(dbegin) + day_in_y(dend) + (year(dend) - year(dbegin) -1) * 365 + (year(dend) - year(dbegin) -1) / 4);
        else
            return (365 - day_in_y(dbegin) + day_in_y(dend) + (year(dend) - year(dbegin) -1) * 365 + (year(dend) - year(dbegin) + year(dbegin) % 4  - 1) / 4);
    }
}
//Get Year from date in yyyymmdd format.
int Date_interval::year(const int &yyyymmdd)
{
    if ((yyyymmdd / 10000 > 9999) || (yyyymmdd / 10000 < 1000))
        return -1;
    else
        return yyyymmdd / 10000;
}

int Date_interval::month(const int &yyyymmdd)
{
    if(((yyyymmdd % 10000) / 100 > 12) || ((yyyymmdd % 10000) / 100 == 0))
        return -1;
    else
        return (yyyymmdd % 10000) / 100;
}

int Date_interval::day(const int &yyyymmdd)
{
    bool leapY_and_mFeb = (leap_y(year(yyyymmdd)) && (month(yyyymmdd) == 2));
    bool ordY_and_mFeb = (!leap_y(year(yyyymmdd)) && (month(yyyymmdd) == 2));
    bool b30days = ((yyyymmdd % 10000) % 100 == 30);
    bool b29days = ((yyyymmdd % 10000) % 100 == 29);
    bool b31days = ((yyyymmdd % 10000) % 100 == 31);
    bool b0days = ((yyyymmdd % 10000) % 100 == 0);
    bool b32days = ((yyyymmdd % 10000) % 100 > 31);
    bool leapY_and_mFeb_and_b30days = (leapY_and_mFeb && b30days); //(Ovaj || b31days_and_m30d) && b0days && b32days
    bool ordY_and_mFeb_and_b29days =  (ordY_and_mFeb&& b29days);
    bool m_30d = ((month(yyyymmdd) == 4) || (month(yyyymmdd) == 6) || (month(yyyymmdd) == 9) || (month(yyyymmdd) == 11));
    bool b31days_and_m30d = b31days && m_30d;

    if (leapY_and_mFeb_and_b30days || b31days_and_m30d || b0days || b32days)
        return -1;
    else if (ordY_and_mFeb_and_b29days || b31days_and_m30d || b0days || b32days)
        return -1;
    else
        return (yyyymmdd % 10000) % 100;
}

