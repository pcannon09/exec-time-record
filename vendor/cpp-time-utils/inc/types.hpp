#pragma once

#include "types.hpp"

#include <string>
#include <vector>

#if __cplusplus >= 199711L

namespace timeUtils
{
    /**
     * @enum TimerStopwatchState
     * @brief Represents the state of a timer or stopwatch.
     */
    enum TimerStopwatchState
    {
        FALSE = 0, ///< Timer/stopwatch is stopped.
        TRUE = 1,  ///< Timer/stopwatch is running.
        PAUSED = 2 ///< Timer/stopwatch is paused.
    };

    /**
     * @struct Timestamp
     * @brief Represents a timestamp.
     */
    typedef struct Timestamp
    {
        unsigned int hour; ///< Hour value.
        unsigned int min;  ///< Minute value.
        unsigned int sec;  ///< Second value.
        unsigned int ms;   ///< Millisecond value.
    } Timestamp;

    /**
     * @struct DateInfo
     * @brief Represents date information.
     */
    typedef struct DateInfo
    {
        unsigned int year;    ///< Year value.
        unsigned int month;   ///< Month value.
        unsigned int day;     ///< Day value.
        unsigned int weekDay; ///< Day of the week.
        unsigned int yearDay; ///< Day of the year.
    } DateInfo;

    /**
     * @struct TimeZoneInfo
     * @brief Represents time zone information.
     */
    typedef struct TimeZoneInfo
    {
        bool isDST;                 ///< Indicates if daylight saving time is active.
        bool gmtOff;                ///< Indicates if GMT offset is applied.
        std::string timezone;       ///< Name of the timezone (e.g., "Spain", "India", "England").
        std::vector<int> utcTimezone; ///< UTC timezone offset in hours and minutes ({hour, min}).
    } TimeZoneInfo;

    /**
     * @struct TimeInfo
     * @brief Represents time information.
     */
    typedef struct TimeInfo
    {
        unsigned int hour; ///< Hour value.
        unsigned int min;  ///< Minute value.
        unsigned int sec;  ///< Second value.
        unsigned int ms;   ///< Millisecond value.

        bool isAm;        ///< Indicates if the time is before 12 PM.
        bool is12hFormat; ///< Indicates if the time is in 12-hour format.
    } TimeInfo;

    /**
     * @struct TimeOffset
     * @brief Represents a time offset.
     */
    typedef struct TimeOffset
    {
        int hour = 0;         ///< Offset hours.
        unsigned int min = 0; ///< Offset minutes.
    } TimeOffset;
}

#endif

