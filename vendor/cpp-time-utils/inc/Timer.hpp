#pragma once

#include "Timer.hpp"

#include <string>

#include "../inc/types.hpp"
#include "../inc/macros.hpp"

#if __cplusplus >= 201102L

#include <chrono>
#include <atomic>

namespace timeUtils
{
    class Timer
    {
    private:
        static std::string id;
        
        static bool hasThread;
        static bool finished;

        static std::atomic<TimerStopwatchState> isRunning;

        static Timestamp progress;
        static Timestamp addProgress;
        static Timestamp duration;

        static unsigned long long targetDurationMs;

        static std::atomic<bool> threadActive;

        static std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::milliseconds elapsedTime;

        /*
         * @brief Count the timer.
         */
        void counter();

        /*
         * @brief Converts a Timestamp to milliseconds.
         * @param ts The Timestamp to be converted.
         * @return The equivalent time in milliseconds.
         */
        unsigned long long timestampToMS(Timestamp ts);

    public:
        /*
         * @brief Constructor to set the ID and duration of the timer.
         * @param id The identifier for the timer.
         * @param duration The duration of the timer.
         */
        Timer(std::string id, Timestamp duration);

        /*
         * @brief Destructor that calls Timer::deleteTimer() to stop the timer.
         */
        ~Timer();

        /*
         * @brief Set the duration of the timer.
         * @param timer The new duration to set.
         */
        void setDuration(Timestamp timer);

        /*
         * @brief Get the ID of the Timer.
         * @return The timer ID as a std::string.
         */
        std::string getID();

        /*
         * @brief Set whether the timer should use a separate thread when running.
         * @param toCreate True to use a separate thread, false otherwise.
         */
        void setThread(bool toCreate);

        /*
         * @brief Start the timer.
         */
        void start();

        /*
         * @brief Stop (pause) the timer.
         */
        void stop();

        /*
         * @brief Reset the timer to its starting value.
         */
        void reset();

        /*
         * @brief Delete the timer and reset everything.
         */
        void deleteTimer();

        /*
         * @brief Set the time according to the given Timestamp.
         * @param time The timestamp to set.
         */
        void set(Timestamp time);

        /*
         * @brief Get the current timestamp from this timer.
         * @return The current timestamp.
         */
        Timestamp get();

        /*
         * @brief Check if the timer is running.
         * @return The current state of the timer as a TimerStopwatchState.
         */
        TimerStopwatchState getIsRunning();

        /*
         * @brief Check if the timer has finished.
         * @return True if the timer has finished, false otherwise.
         */
        bool isFinished();
    };
}

#else
namespace timeUtils
{
    class Timer
    { };
}

#   warning "Current CXX standard not supported"
#   pragma message("CXX Standard: " STT_TOSTRING(__cplusplus))

#endif

