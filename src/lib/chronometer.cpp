/**
 * @file chronometer.cpp
 * @brief Implementation of etr::Chronometer.
 */

#include "exec_time_record/chronometer.hpp"

#include "cpp-time-utils/inc/Sleep.hpp"

#include <atomic>
#include <thread>

namespace etr
{
	// PRIVATE //
	float Chronometer::__elapsed()
	{
		const timeUtils::Timestamp ts = this->chronoStopwatch.get();

		return ts.hour * 3600.0f + ts.min * 60.0f +
			static_cast<float>(ts.sec) + ts.ms * 0.001f;
	}

	bool Chronometer::__reachedEnd()
	{
		if (this->end < 0.0f)
			return false;

		return this->__elapsed() >= this->end;
	}

	// PROTECTED //
	bool Chronometer::__startCount()
	{
		this->chronoStopwatch.setThread(true);
		this->chronoStopwatch.start();

		return true;
	}

	bool Chronometer::__endCount()
	{
		return true;
	}

	bool Chronometer::__exec(std::function<void()> func)
	{
		if (this->end < 0.0f)
		{
			func();
			return true;
		}

		std::atomic<bool> active{true};

		std::thread watch([this, &active]() {
			while (active.load())
			{
				if (this->__reachedEnd())
				{
					this->stop();
					this->__endCount();
					break;
				}

				timeUtils::Sleep("").milliseconds(1);
			}
		});

		func();

		active.store(false);
		if (watch.joinable())
			watch.join();

		return true;
	}

	// PUBLIC //
	Chronometer::Chronometer(ChronoResult *result, const float startDelay, const float end)
		: result_(result), startDelay(startDelay), end(end)
	{
		if (this->result_)
			*this->result_ = {};
	}

	Chronometer::~Chronometer()
	{ this->exit(); }

	void Chronometer::pause()
	{
		this->chronoState_ = ChronoState::Paused;
	}

	void Chronometer::clear()
	{
		this->result_ = {};
	}

	void Chronometer::run(std::function<void()> func)
	{
		if (startDelay >= 0.0f)
			timeUtils::Sleep("").seconds(this->startDelay);

		this->chronoStopwatch.reset();
		this->chronoState_ = ChronoState::Started;
		this->__startCount();
		this->__exec(func);
	}

	void Chronometer::stop()
	{
		if (this->chronoState_ == ChronoState::Stopped)
			return;

		if (this->result_)
			this->result_->timestampTotal = this->chronoStopwatch.get();

		this->chronoStopwatch.stop();
		this->chronoStopwatch.reset();
		this->chronoState_ = ChronoState::Stopped;
	}

	ChronoResult Chronometer::exit()
	{
		this->stop();

		return this->result_ ? *this->result_ : ChronoResult{};
	}
}
