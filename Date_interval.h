#ifndef DATE_INTERVAL_H
#define DATE_INTERVAL_H

class Date_interval
{
    public:
        Date_interval();
        Date_interval(const int &dbegin, const int &dend);
        int calculate(const int &dbegin, const int &dend);
        int day_in_y(const int &yyyymmdd);
        int year(const int &yyyymmdd);
        int month(const int &yyyymmdd);
        int day(const int &yyyymmdd);
        int get_Interval();
        int ordinal_to_d(const int &ordinal, const int &dyear);
        bool leap_y(const int &dYear);

    protected:
    private:
        int m_begin;
        int m_end;
        int m_interval;
};

#endif // DATE_INTERVAL_H
