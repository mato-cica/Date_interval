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

/* - The Function get a value of m_interval class member
 * - arguments: no
 * - return: integer representing interval between two dates  */
int Date_interval::get_Interval()
{
    return m_interval;
}

/* - The Function checks for a leap year status
 * - arguments: dYear is an integer representing the year
 * - return: bool representing leap year status of the dYear  */
bool Date_interval::leap_y(const int &dYear)
{
    return (dYear % 4 == 0);
}

/* - The Function calculates ordinal number of the day in the date in yyyymmdd format.
 * - arguments: yyyymmdd is an integer representing the date in the form of 'yyyymmdd'
 * - return: integer representing ordinal number of the day in the date in the form
 *   of yyyymmdd  */
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

/* - The Function calculates the date in yyyymmdd format based on ordinal number of
 *   the day in the year
 * - arguments: ordinal is an integer representing ordinal number of the day in the year,
 *   dyear is integer representing a year
 * - return: integer representing the date in the form of yyyymmdd or -1 in case of an error  */
int Date_interval::ordinal_to_d(const int &ordinal, const int &dyear)
{
    int ord_year[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap_year[12] {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ord_sum[12] {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int leap_sum[12] {31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
    if(ordinal > 366 || ordinal < 1)
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
                    if(ordinal <= leap_sum[i])
                        return dyear * 10000 + (i + 1) * 100 + leap_year[i] - (leap_sum[i] - ordinal);
                }
            }
            else
            {
                for(int i = 0; i < 12; ++i)
                {
                    if(ordinal <= ord_sum[i])
                        return dyear * 10000 + (i + 1) * 100 + ord_year[i] - (ord_sum[i] - ordinal);
                }
            }
        }
    }
    return 0;
}

/* - The Function calculates interval in days between two dates in yyyymmdd format
 * - arguments: dbegin and dend are integers representing date in the form of 'yyyymmdd'
 * - return: integer representing the number of days between dbegin and dend  */
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

/* - The Function calculates the year in date in the form of 'yyyymmdd'
 * - arguments: yyyymmdd is an integer representing date in the form of 'yyyymmdd'
 * - return: integer representing the day in the date in the form of yyyymmdd or -1
 *   in case of an error  */
int Date_interval::year(const int &yyyymmdd)
{
    if ((yyyymmdd / 10000 > 9999) || (yyyymmdd / 10000 < 1000))
        return -1;
    else
        return yyyymmdd / 10000;
}

/* - The Function calculates the month in date in the form of 'yyyymmdd'
 * - arguments: yyyymmdd is an integer representing date in the form of 'yyyymmdd'
 * - return: integer representing the year in the date in the form of yyyymmdd or -1
 *   in case of an error  */
int Date_interval::month(const int &yyyymmdd)
{
    if(((yyyymmdd % 10000) / 100 > 12) || ((yyyymmdd % 10000) / 100 == 0))
        return -1;
    else
        return (yyyymmdd % 10000) / 100;
}

/* - The Function calculates the day in date in the form of 'yyyymmdd'
 * - arguments: yyyymmdd is an integer representing date in the form of 'yyyymmdd'
 * - return: integer representing the month in the date in the form of yyyymmdd or -1
 *   in case of an error  */
int Date_interval::day(const int &yyyymmdd)
{
    bool leapY_and_mFeb = (leap_y(year(yyyymmdd)) && (month(yyyymmdd) == 2));
    bool ordY_and_mFeb = (!leap_y(year(yyyymmdd)) && (month(yyyymmdd) == 2));
    bool b30days = ((yyyymmdd % 10000) % 100 == 30);
    bool b29days = ((yyyymmdd % 10000) % 100 == 29);
    bool b31days = ((yyyymmdd % 10000) % 100 == 31);
    bool b0days = ((yyyymmdd % 10000) % 100 == 0);
    bool b32days = ((yyyymmdd % 10000) % 100 > 31);
    bool leapY_and_mFeb_and_b30days = (leapY_and_mFeb && b30days);
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
/* - The Function calculates date nDays after the date yyyymmdd.
 * - arguments: yyyymmdd is an integer representing date in the form of yyyymmdd,
 *   nDays integer representing number of days to be added
 * - return: integer representing the date in the form of yyyymmdd  */
int Date_interval::after(const int &yyyymmdd, const int &nDays)
{
    /* If it is the same year - end of story */
    if(leap_y(year(yyyymmdd)) && ((day(yyyymmdd) + nDays) <= 366))
        return ordinal_to_d(day(yyyymmdd) + nDays, year(yyyymmdd));
    if(!leap_y(year(yyyymmdd)) && ((day(yyyymmdd) + nDays) <= 365))
        return ordinal_to_d(day(yyyymmdd) + nDays, year(yyyymmdd));

    int firstDofY = 0;
    int daysNextY = 0;

    if(leap_y(year(yyyymmdd)))
        daysNextY = nDays - (366 - day_in_y(yyyymmdd) + 1);
    else
        daysNextY = nDays - (365 - day_in_y(yyyymmdd) + 1);

    firstDofY = (year(yyyymmdd) +1) * 10000 + 101;

    /* Try with 1st of January next year with difference between nDays and 365 (366)
       and day(yyyymmdd) */
    after(firstDofY, daysNextY);   // recursion
}

/* - The Function calculates date nDays before the date yyyymmdd.
 * - arguments: yyyymmdd is an integer representing date in the form of yyyymmdd,
 *   nDays integer representing number of days to be subtracted
 * - return: integer representing the date in the form of yyyymmdd  */
int Date_interval::before(const int &yyyymmdd, const int &nDays)
{
    if(day_in_y(yyyymmdd) > nDays)    // Same year
        return ordinal_to_d(day_in_y(yyyymmdd) - nDays, year(yyyymmdd));

    int lastDofY = 0;
    int daysLastY = nDays - day_in_y(yyyymmdd);
    lastDofY = (year(yyyymmdd) - 1) * 10000 + 12 * 100 + 31;
    /* Try with 31st of December last year with difference between nDays and day(yyyymmdd) */
    before(lastDofY, daysLastY);   // recursion
}

