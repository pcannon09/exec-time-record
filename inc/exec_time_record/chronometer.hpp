#ifndef INCLUDE_EXEC_TIME_RECORD_CHRONOMETER_HPP_
#define INCLUDE_EXEC_TIME_RECORD_CHRONOMETER_HPP_

#include <functional>

#include "cpp-time-utils/inc/Stopwatch.hpp"

namespace etr
{
	enum class ChronoState
	{
		NotStarted,
		Stopped,

		Started,
		Paused,
		Continued,
	};

	typedef struct ChronoResult
	{
		timeUtils::Timestamp timestampTotal;
	} ChronoResult;

	class Chronometer
	{
	private:
		ChronoState chronoState_ = ChronoState::NotStarted;
		ChronoResult *result_ = nullptr;

		float __elapsed();
		bool __reachedEnd();

	protected:
		timeUtils::Stopwatch chronoStopwatch =
			timeUtils::Stopwatch("");

		virtual bool __startCount();
		virtual bool __endCount();
		virtual bool __exec(std::function<void()> func);

	public:
		const float startDelay = 0.0f;
		const float end = -1.0f; // Ignore if lower than: 0.0f

		Chronometer(ChronoResult *result, const float startDelay = 0.0f, const float end = -1.0f);
		~Chronometer();

		void clear();
		void pause();
		void stop();

		void run(std::function<void()> func);

		ChronoResult exit();

		inline ChronoResult getResult() const
		{ return this->result_ ? *this->result_ : ChronoResult{}; }

		inline ChronoState getState()
		{ return this->chronoState_; }

		inline bool isFinished()
		{ return this->chronoState_ == ChronoState::Stopped; }
	};
}

#endif  // INCLUDE_EXEC_TIME_RECORD_CHRONOMETER_HPP_
