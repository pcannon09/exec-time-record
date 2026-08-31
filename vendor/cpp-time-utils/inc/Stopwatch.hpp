#pragma once

#include "../inc/macros.hpp"

#if __cplusplus >= 201103L

#include <string>
#include <chrono>
#include <atomic>

#include "../inc/types.hpp"

namespace timeUtils
{
    class Stopwatch
    {
    private:
		std::string id;

		bool hasThread;

		static inline std::atomic<TimerStopwatchState> isRunning{FALSE};

		Timestamp progress = {0, 0, 0, 0};
		Timestamp addProgress = {0, 0, 0, 0};

		static inline std::atomic<bool> threadActive{false};

		std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::milliseconds elapsedTime;

        /*
         * Counter - Function
         * @brief Add the stopwatch to the counter
         */
        void counter();

    public:
        /*
         * Stopwatch - Constructor
         * @brief Set the ID of the stopwatch
         * @param id
         */
        Stopwatch(std::string id);
        
        /*
         * Stopwatch - Deconstructor
         * @brief Call the `deleteWatch()` function to stop the stopwatch
         */
        ~Stopwatch();

        /*
         * Get ID - Function
         * @brief Get the ID of the Stopwatch
         * @return std::string
         */
        std::string getID();

        /*
         * Set Thread - Function
         * @brief Set if it should use a separate thread when running the stopwatch
         * @param toCreate
         */
        void setThread(bool toCreate);

        /*
         * Start - Function
         * @brief Start the stopwatch
         */
        void start();

        /*
         * Stop - Function
         * @brief Stop ( Pause ) the stopwatch
         */
        void stop();

        /*
         * @brief Reset the timer to its starting value.
         */
        void reset();

        /*
         * @brief Delete the watch and reset everything.
         */
        void deleteWatch();

        /*
         * @brief Set the time according to the given Timestamp.
         * @param time The timestamp to set the watch to.
         */
        void set(Timestamp time);

        /*
         * @brief Get the current timestamp from this watch.
         * @return The current timestamp.
         */
        Timestamp get();

        /*
         * @brief Check if the timer is running.
         * @return The current state of the timer as a TimerStopwatchState.
         */
        TimerStopwatchState getIsRunning();
    };
}

#else
namespace timeUtils
{
    class Stopwatch
    { };
}

#   warning "Current CXX standard not supported"
#   pragma message("CXX Standard: " STT_TOSTRING(__cplusplus))

#endif

