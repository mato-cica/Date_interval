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

int Date_interval::after(const int &yyyymmdd, const int &nDays)
{
    int no_of_years = nDays / 365;
    int restDays = nDays % 365;
    int noOfDaysBY = 365;
    int result_year = year(yyyymmdd) + no_of_years;
    int correction = 0;

    if(leap_y(year(yyyymmdd)))
    {
        if(nDays < 366)
            restDays = nDays % 366;
        noOfDaysBY = 366;
    }

    bool sameYear = day_in_y(yyyymmdd) + restDays <= noOfDaysBY;

    if(sameYear && nDays < noOfDaysBY)
        result_year = year(yyyymmdd);

    int result_dayInYear = day_in_y(yyyymmdd) + restDays;

    int distFromLeapY = year(yyyymmdd) % 4;
    //bool nonEff_leapYear = leap_y(year(yyyymmdd)) && day_in_y(yyyymmdd) > 59;

    if(nDays > noOfDaysBY)
        if(distFromLeapY > result_year % 4)
        {
            correction = 1;
            if(leap_y(result_year))
                correction = 0;
        }
    if(result_dayInYear > noOfDaysBY)
    {
        result_dayInYear = result_dayInYear - noOfDaysBY;
        result_year = result_year + 1;
    }

    result_dayInYear = result_dayInYear - (result_year - year(yyyymmdd))/4 - correction;
    if(result_dayInYear < 1)
    {
        result_year = result_year - 1;
        if(leap_y(result_year))
            result_dayInYear = 366 + result_dayInYear;
        else
            result_dayInYear = 365 + result_dayInYear;
    }
    return ordinal_to_d(result_dayInYear, result_year);
}

int Date_interval::before(const int &yyyymmdd, const int &nDays)
{
    int no_of_years = nDays/365;
    int result_year = 0;
    int result_dayInYear = 0;
    int dec31_lastYear = (year(yyyymmdd) - no_of_years) * 10000 + 1231;

    bool yearDiff_1 = 0;
    bool yearDiff_2 = 0;
    bool yearDiff_3 = 0;
    bool yearDiff_4 = 0;

    bool leapY_1up = 0;
    bool leapY_1or2up = 0;
    bool leapY_1or2or3up = 0;

    if(nDays % 365 != 0)
    {
        if(nDays % 365 <= day_in_y(yyyymmdd))
        {
            if(nDays % 365 == day_in_y(yyyymmdd))
            {
                if(nDays < 365)
                    return (year(yyyymmdd) - 1) * 10000 + 1231; // 31st of December last year
                else
                {
                    result_year = year(yyyymmdd) - no_of_years;
                    result_dayInYear = day_in_y(dec31_lastYear) - (nDays - day_in_y(yyyymmdd));
                    return ordinal_to_d(result_dayInYear, result_year);
                }
            }
            else  /*  nDays % 365 < day_in_y(yyyymmdd)  */
            {
                result_year = year(yyyymmdd) - no_of_years;
                if(nDays < 365)
                {
                    result_dayInYear = day_in_y(yyyymmdd) - nDays % 365;
                    return ordinal_to_d(result_dayInYear, result_year);
                }
                else  /* nDays > 365 */
                {
                    result_dayInYear = day_in_y(dec31_lastYear) - (nDays - day_in_y(yyyymmdd));
                    return ordinal_to_d(result_dayInYear, result_year);
                }
            }
        }
        else  /* nDays % 365 > day_in_y(yyyymmdd) */
        {
            result_year = year(yyyymmdd) - no_of_years - 1;
            dec31_lastYear = result_year * 10000 + 1231;
            result_dayInYear = day_in_y(dec31_lastYear) - (nDays % 365 - day_in_y(yyyymmdd));

            yearDiff_1 = year(yyyymmdd) - result_year == 1;
            yearDiff_2 = year(yyyymmdd) - result_year == 2;
            yearDiff_3 = year(yyyymmdd) - result_year == 3;
            yearDiff_4 = year(yyyymmdd) - result_year == 4;

            leapY_1up = leap_y(result_year + 1);
            leapY_1or2up = leap_y(result_year + 1) || leap_y(result_year + 2);
            leapY_1or2or3up = leap_y(result_year + 1) || leap_y(result_year + 2) || leap_y(result_year + 3);

            if(yearDiff_1 || (yearDiff_2 && !leapY_1up) || (yearDiff_3 && !leapY_1or2up) || (yearDiff_4 && !leapY_1or2or3up))
                return ordinal_to_d(result_dayInYear, result_year);
            if((yearDiff_2 && leapY_1up) || (yearDiff_3 && leapY_1or2up) || (yearDiff_4 && leapY_1or2or3up))
                return ordinal_to_d(result_dayInYear + 1, result_year);

            result_dayInYear = result_dayInYear + (year(yyyymmdd) - result_year)/4;

            if((result_dayInYear > 366) && leap_y(result_year))
            {
                result_dayInYear = result_dayInYear - 366;
                result_year = result_year + 1;
            }
            if(result_dayInYear > 365 && !leap_y(result_year))
            {
                result_dayInYear = result_dayInYear - 365;
                result_year = result_year + 1;
            }

            return ordinal_to_d(result_dayInYear, result_year);
        }
    }
    else   /* nDays % 365 = 0 */
    {
        result_year = year(yyyymmdd) - no_of_years;
        dec31_lastYear = result_year * 10000 + 1231;
        if(leap_y(yyyymmdd))
            result_dayInYear = day_in_y(dec31_lastYear) - (366 - day_in_y(yyyymmdd));
        else
            result_dayInYear = day_in_y(dec31_lastYear) - (365 - day_in_y(yyyymmdd));

        if(nDays == 0)
            return yyyymmdd;

        yearDiff_1 = year(yyyymmdd) - result_year == 1;
        yearDiff_2 = year(yyyymmdd) - result_year == 2;
        yearDiff_3 = year(yyyymmdd) - result_year == 3;

        leapY_1up = leap_y(result_year + 1);
        leapY_1or2up = leap_y(result_year + 1) || leap_y(result_year + 2);
        leapY_1or2or3up = leap_y(result_year + 1) || leap_y(result_year + 2) || leap_y(result_year + 3);

        if((yearDiff_1 && month(yyyymmdd) == 12) && (day(yyyymmdd) == 31 && leapY_1up))
            return (result_year + 1) * 10000 + 101;
        if((yearDiff_1 && leapY_1up) || (yearDiff_2 && leapY_1or2up) || (yearDiff_3 && leapY_1or2or3up))
            return ordinal_to_d(result_dayInYear, result_year);
        if((yearDiff_1 && !leapY_1up) || (yearDiff_2 && !leapY_1or2up) || (yearDiff_3 && !leapY_1or2or3up))
            return result_year * 10000 + month(yyyymmdd) * 100 + day(yyyymmdd);

        result_dayInYear = result_dayInYear + (year(yyyymmdd) - result_year)/4;

        if((result_dayInYear > 366) && leap_y(result_year))
        {
            result_dayInYear = result_dayInYear - 366;
            result_year = result_year + 1;
        }
        if(result_dayInYear > 365 && !leap_y(result_year))
        {
            result_dayInYear = result_dayInYear - 365;
            result_year = result_year + 1;
        }
        return ordinal_to_d(result_dayInYear, result_year);
    }
}

