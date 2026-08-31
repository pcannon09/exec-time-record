#pragma once

#include "../inc/macros.hpp"

#include <string>

#if __cplusplus >= 201103L

namespace timeUtils
{
    class Sleep
    {
    private:
        std::string id;

    public:
        /*
         * @brief Constructor to create the Sleep object.
         * @param ID The identifier for the Sleep object.
         */
        Sleep(std::string ID);

        /*
         * @brief Sleep for a specified number of hours.
         * @param duration The number of hours to sleep.
         */
        void hours(unsigned int duration);

        /*
         * @brief Sleep for a specified number of minutes.
         * @param duration The number of minutes to sleep.
         */
        void minutes(unsigned int duration);

        /*
         * @brief Sleep for a specified number of seconds.
         * @param duration The number of seconds to sleep.
         */
        void seconds(unsigned int duration);

        /*
         * @brief Sleep for a specified number of decimal seconds.
         * @param duration The number of seconds to sleep (with decimal precision).
         */
        void seconds(double duration);

        /*
         * @brief Sleep for a specified number of milliseconds.
         * @param duration The number of milliseconds to sleep.
         */
        void milliseconds(unsigned int duration);

        /*
         * @brief Sleep for a specified number of nanoseconds.
         * @param duration The number of nanoseconds to sleep.
         */
        void nanoseconds(unsigned int duration);

        /*
         * @brief Get the ID of this Sleep object.
         * @return The ID as a std::string.
         */
        std::string getID();
    };
}

#else
namespace timeUtils
{
    class Sleep
    { };
}

#   warning "Current CXX standard not supported"
#   pragma message("CXX Standard: " STT_TOSTRING(__cplusplus))

#endif

