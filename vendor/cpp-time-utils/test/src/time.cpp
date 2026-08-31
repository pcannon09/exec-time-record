#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "../../inc/Time.hpp"

#if __cplusplus >= 199711L
namespace tests
{
    int time()
    {
        timeUtils::Time time("main");

        timeUtils::TimeZoneInfo tzInfo;
        timeUtils::DateInfo dateInfo;
        timeUtils::TimeInfo timeInfo;

        time.setUTCOffset(11, 59);
        time.addOffset(1, 1);

        timeInfo.is12hFormat = time.set12hFormat(true);

        while (1)
        {
            time.update(tzInfo);
            time.update(dateInfo);
            time.update(timeInfo);

            std::cout
                << "- TIME ZONE INFO -\n"
                << "GMT Off? : " << tzInfo.gmtOff << "\n"
                << "Is DST? : " << tzInfo.isDST << "\n"
                << "Current timezone : " << tzInfo.timezone << "\n"
                << "Current UTC timezone : UTC " << 
                    (tzInfo.utcTimezone[0]) << ":" <<
                    tzInfo.utcTimezone[1] << "\n"
                << "UTC Offset: " << time.getUTCOffset().hour << " : " <<time.getUTCOffset().min << "\n"
                << "Add Offset: " << time.getAddOffset().hour << " : " <<time.getAddOffset().min << "\n"

                << "- TIME INFO -\n"
                << "Hour: " << timeInfo.hour <<  "\n"
                << "Min : " << timeInfo.min << "\n"
                << "Sec : " << timeInfo.sec << "\n"
                << "MS : " << timeInfo.ms << "\n"
                << "Is AM? : " << timeInfo.isAm << "\n"
                << "Is 12 hour format? : " << timeInfo.is12hFormat << "\n"

                << "- DATE INFO -\n"
                << "Year : " << dateInfo.year << "\n"
                << "Month : " << dateInfo.month << "\n"
                << "Day : " << dateInfo.day << "\n"
                << "Week day : " << dateInfo.weekDay << "\n"
                << "Year day : " << dateInfo.yearDay << "\n"

                << "\r" << std::flush;

            system("clear");
        }

        return 0;
    }
}

#else
namespace tests
{ int time() { return -1; } }

#endif
