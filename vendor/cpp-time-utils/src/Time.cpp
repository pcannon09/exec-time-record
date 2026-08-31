#include <string>
#include <ctime>

#include "../inc/Time.hpp"
#include "../inc/types.hpp"

#if __cplusplus >= 201103L
#   include <chrono>
#endif

#if __cplusplus >= 199711L

namespace timeUtils
{
    std::string Time::id;

    int Time::utcHourOffset = 0;
    unsigned int Time::utcMinOffset = 0;

    int Time::addHourOffset = 0;
    unsigned int Time::addMinOffset = 0;

    DateInfo Time::dateInfo;

    Time::Time(std::string ID)
    { this->id = ID; }

    // TIME
    int Time::update(DateInfo &info)
    {
        std::time_t now = std::time(NULL);
        std::tm *local = std::localtime(&now);

        if (local)
        {
            info.year = local->tm_year + 1900;
            info.month = local->tm_mon + 1;
            info.day = local->tm_mday;
            info.weekDay = local->tm_wday;
            info.yearDay = local->tm_yday;

            this->dateInfo = info;

            // Offset check
            if (utcHourOffset >= 12)
            {
                info.day++;
                info.weekDay++;
                info.yearDay++;

                if (info.day > this->getDaysInMonth())
                {
                    if (info.yearDay >= 
                            ((this->dateInfo.year % 4 == 0 && this->dateInfo.year % 100 != 0) || (this->dateInfo.year % 400 == 0) ?
                            366 : 365))
                    {
                        info.day = 1;
                        info.weekDay = 1;
                        info.yearDay = 1;

                        info.year++;
                    }
                }

                this->dateInfo = info;
            }

            return 0;
        }

        return -1;
    }

    unsigned int Time::getDaysInMonth()
    {
        // Handle Feb (leap year check)
        if (this->dateInfo.month == 2) return (this->dateInfo.year % 4 == 0 && this->dateInfo.year % 100 != 0) || (this->dateInfo.year % 400 == 0);

        // Apr, Jun, Sep, Nov have 30 days
        if (this->dateInfo.month == 4 || this->dateInfo.month == 6 || this->dateInfo.month == 9 || this->dateInfo.month == 11) return 30;

        // The rest have 31 days
        return 31;
    }

    // TIME ZONE
    int Time::update(TimeZoneInfo &info)
    {
        std::time_t now = std::time(NULL);
        std::tm *local = std::localtime(&now);
        std::tm *utc = std::gmtime(&now);

        if (local && utc)
        {
            int  utcOffsetSecs = std::difftime(std::mktime(local), std::mktime(utc));

            int hours = (utcOffsetSecs) / 3600;
            int mins = (utcOffsetSecs % 3600) / 60;

            info.timezone = local->tm_zone;
            info.isDST = local->tm_isdst;
            info.gmtOff = local->tm_gmtoff;

            info.utcTimezone.clear();
            info.utcTimezone.push_back(hours);
            info.utcTimezone.push_back(mins);

            return 0;
        }

        return -1;
    }

    // DATE
#if __cplusplus >= 201102L
    int Time::update(TimeInfo &info)
    {
        std::time_t now = std::time(NULL);
        std::tm *local = std::localtime(&now);

        if (local)
        {
            auto now = std::chrono::system_clock::now();

            auto duration = now.time_since_epoch();
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;

            int adjHour = 0;
            int adjMin = 0;

            adjHour = local->tm_hour + this->utcHourOffset + this->addHourOffset;
            adjMin = local->tm_min + this->utcMinOffset + this->addMinOffset;

            if (adjMin >= 60)
            {
                adjHour += adjMin / 60;
                adjMin %= 60;
            }

            if (adjHour >= 24)
            { adjHour %= 24; }

            else if (adjHour < 0)
            { adjHour += 24; }

            info.hour = (info.is12hFormat) ? 
                        ((adjHour == 0 || adjHour == 12) ? 12 : adjHour % 12)
                      : adjHour;
                      
            info.min = adjMin;
            info.sec = local->tm_sec;
            info.ms = ms.count();
            info.isAm = (adjHour < 12);

            return 0;
        }

        return -1;
    }

#else
    int Time::update(TimeInfo &info)
    {
        std::time_t now = std::time(NULL);
        std::tm *local = std::localtime(&now);

        if (local)
        {
            int adjHour = local->tm_hour + this->utcHourOffset + this->addHourOffset;
            int adjMin = local->tm_min + this->utcMinOffset + this->addMinOffset;

            if (adjMin >= 60)
            {
                adjHour += adjMin / 60;
                adjMin %= 60;
            }

            if (adjHour >= 24)
            { adjHour %= 24; }

            else if (adjHour < 0)
            { adjHour += 24; }

            info.hour = (info.is12hFormat) ? 
                        ((adjHour == 0 || adjHour == 12) ? 12 : adjHour % 12)
                      : adjHour;
                      
            info.min = adjMin;
            info.sec = local->tm_sec;
            info.ms = 0; // Set milliseconds to 0 (C++98 does not support chrono)
            info.isAm = (adjHour < 12);

            return 0;
        }

        return -1;
    }
#endif

    void Time::setUTCOffset(int hour, unsigned int min)
    {
        this->utcHourOffset = std::max(-12, std::min(hour, 14)); // Range of UTC-12:00 to UTC+14:00
        this->utcMinOffset = std::max(0, std::min((int)min, 60));
    }

    void Time::addOffset(int hour, unsigned int min)
    {
        this->addHourOffset = hour;
        this->addMinOffset = min;
    }

    TimeOffset Time::getUTCOffset()
    {
        TimeOffset offset = {};

        offset.hour = this->utcHourOffset;
        offset.min = this->utcMinOffset;

        return offset;
    }

    TimeOffset Time::getAddOffset()
    {
        TimeOffset offset = {};

        offset.hour = this->addHourOffset;
        offset.min = this->addMinOffset;

        return offset;
    }

    bool Time::set12hFormat(bool set12hFormat)
    { return set12hFormat; }

    std::string Time::getID()
    { return this->id; }
}

#endif
