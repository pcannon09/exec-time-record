#ifndef INCLUDE_EXEC_TIME_RECORD_CHRONOMETER_HPP_
#define INCLUDE_EXEC_TIME_RECORD_CHRONOMETER_HPP_

#include <functional>

#include "cpp-time-utils/inc/Stopwatch.hpp"

/**
 * @file chronometer.hpp
 * @brief Public API for timing callable code blocks.
 */

/**
 * @namespace etr
 * @brief exec-time-record library namespace.
 */
namespace etr
{
	/**
	 * @enum ChronoState
	 * @brief Lifecycle state of a Chronometer instance.
	 */
	enum class ChronoState
	{
		NotStarted, ///< Constructed but not yet run.
		Stopped,    ///< Timing finished (via stop or exit).

		Started,    ///< Currently measuring.
		Paused,     ///< Temporarily paused.
		Continued,  ///< Resumed after a pause.
	};

	/**
	 * @struct ChronoResult
	 * @brief Accumulated timing result written by Chronometer.
	 */
	typedef struct ChronoResult
	{
		timeUtils::Timestamp timestampTotal; ///< Total elapsed time (h/m/s/ms).
	} ChronoResult;

	/**
	 * @class Chronometer
	 * @brief Runs a callable and records how long it takes.
	 *
	 * Optionally waits @ref startDelay seconds before starting, and can stop
	 * automatically when @ref end seconds of measured time have elapsed
	 * (@c end < 0 disables that limit).
	 *
	 * @code
	 * etr::ChronoResult result{};
	 * etr::Chronometer chrono(&result);
	 * chrono.run([]() { // timed work
	 * });
	 * etr::ChronoResult done = chrono.exit();
	 * @endcode
	 */
	class Chronometer
	{
	private:
		ChronoState chronoState_ = ChronoState::NotStarted;
		ChronoResult *result_ = nullptr;

		/**
		 * @brief Elapsed measured time in seconds.
		 * @return Seconds since the stopwatch started (paused time excluded by the stopwatch).
		 */
		float __elapsed();

		/**
		 * @brief Whether the optional @ref end duration has been reached.
		 * @return @c true if @ref end is set and elapsed time is past it.
		 */
		bool __reachedEnd();

	protected:
		timeUtils::Stopwatch chronoStopwatch =
			timeUtils::Stopwatch("");

		/**
		 * @brief Start the underlying stopwatch.
		 * @return @c true on success.
		 */
		virtual bool __startCount();

		/**
		 * @brief Hook called when an automatic end limit is hit.
		 * @return @c true on success.
		 */
		virtual bool __endCount();

		/**
		 * @brief Execute @p func, optionally watching for the @ref end limit.
		 * @param func Callable to time.
		 * @return @c true on success.
		 */
		virtual bool __exec(std::function<void()> func);

	public:
		const float startDelay = 0.0f; ///< Seconds to sleep before timing starts.
		const float end = -1.0f;       ///< Max measured seconds; ignored if < 0.

		/**
		 * @brief Construct a chronometer that writes into @p result.
		 * @param result Output pointer for the final timestamp (may be @c nullptr).
		 * @param startDelay Seconds to wait before @ref run starts timing.
		 * @param end Max measured duration in seconds; @c < 0 means no limit.
		 */
		Chronometer(ChronoResult *result, const float startDelay = 0.0f, const float end = -1.0f);

		/**
		 * @brief Destructor; calls @ref exit to finalize timing if still active.
		 */
		~Chronometer();

		/**
		 * @brief Clear the stored result pointer association.
		 */
		void clear();

		/**
		 * @brief Mark the chronometer as paused.
		 */
		void pause();

		/**
		 * @brief Stop timing and copy the stopwatch reading into @ref ChronoResult.
		 */
		void stop();

		/**
		 * @brief Apply @ref startDelay, then time @p func until it returns (or @ref end).
		 * @param func Callable whose wall duration is measured.
		 */
		void run(std::function<void()> func);

		/**
		 * @brief Stop if needed and return the current result.
		 * @return Copy of @ref ChronoResult, or an empty result if none was set.
		 */
		ChronoResult exit();

		/**
		 * @brief Current result without stopping.
		 * @return Copy of the result, or empty if @c result was @c nullptr.
		 */
		inline ChronoResult getResult() const
		{ return this->result_ ? *this->result_ : ChronoResult{}; }

		/**
		 * @brief Current lifecycle state.
		 */
		inline ChronoState getState()
		{ return this->chronoState_; }

		/**
		 * @brief Whether timing has finished (@ref ChronoState::Stopped).
		 */
		inline bool isFinished()
		{ return this->chronoState_ == ChronoState::Stopped; }
	};
}

#endif  // INCLUDE_EXEC_TIME_RECORD_CHRONOMETER_HPP_
