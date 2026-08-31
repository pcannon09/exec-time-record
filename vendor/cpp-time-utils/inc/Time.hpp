#pragma once

#include "../inc/macros.hpp"

// #if __cplusplus >= 201103L
#if __cplusplus >= 199711L

#include <string>

#include "../inc/types.hpp"

namespace timeUtils
{
    class Time
    {
    private:
        static std::string id;

        static int utcHourOffset;
        static unsigned int utcMinOffset;

        static int addHourOffset;
        static unsigned int addMinOffset;

        static DateInfo dateInfo;

    public:
        /*
         * @brief Constructor to set the ID of the Time object.
         * @param ID The identifier for the Time object.
         */
        Time(std::string ID);

        /*
         * @brief Set the UTC offset.
         * @param hour The hour offset.
         * @param min The minute offset.
         */
        void setUTCOffset(int hour, unsigned int min);

        /*
         * @brief Set the offset according to your current timezone.
         * @param hour The hour offset.
         * @param min The minute offset.
         */
        void addOffset(int hour, unsigned int min);

        /*
         * @brief Get the previously added UTC offset.
         * @return The UTC offset as a TimeOffset object.
         */
        TimeOffset getUTCOffset();

        /*
         * @brief Get the previously added offset.
         * @return The added offset as a TimeOffset object.
         */
        TimeOffset getAddOffset();

        /*
         * @brief Get the number of days in the current month.
         * @return The number of days in the month.
         */
        unsigned int getDaysInMonth();

        /*
         * @brief Set the Time information and return success (0) or failure (-1).
         * @param info The TimeInfo object containing the new time data.
         * @return 0 if successful, -1 otherwise.
         */
        int update(TimeInfo &info);

        /*
         * @brief Set the Timezone information and return success (0) or failure (-1).
         * @param info The TimeZoneInfo object containing the new timezone data.
         * @return 0 if successful, -1 otherwise.
         */
        int update(TimeZoneInfo &info);

        /*
         * @brief Set the Date information and return success (0) or failure (-1).
         * @param info The DateInfo object containing the new date data.
         * @return 0 if successful, -1 otherwise.
         */
        int update(DateInfo &info);

        /*
         * @brief Set whether to use the 12-hour format.
         * @param set12hFormat True to enable 12-hour format, false otherwise.
         * @return True if successfully set, false otherwise.
         */
        bool set12hFormat(bool set12hFormat);

        /*
         * @brief Get the ID for the Time object.
         * @return The ID as a std::string.
         */
        std::string getID();
    };
}

#else
namespace timeUtils
{
    class Time
    { };
}

#   warning "Current CXX standard not fully supported"
#   pragma message("CXX Standard: " STT_TOSTRING(__cplusplus))

#endif

