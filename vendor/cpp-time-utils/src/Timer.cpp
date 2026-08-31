#include <string>

#include "../inc/Timer.hpp"
#include "../inc/types.hpp"

#if __cplusplus >= 201102L

#include <chrono>
#include <thread>
#include <atomic>

namespace timeUtils
{
    // PRIVATE
    std::string Timer::id;

    bool Timer::hasThread;
    bool Timer::finished = false;

    Timestamp Timer::progress = {0, 0, 0, 0};
    Timestamp Timer::addProgress = {0, 0, 0, 0};
    Timestamp Timer::duration = {0, 0, 0, 0};

    unsigned long long Timer::targetDurationMs;

    std::atomic<bool> Timer::threadActive{false};
    std::atomic<TimerStopwatchState> Timer::isRunning{FALSE};

    std::chrono::high_resolution_clock::time_point Timer::startTime;

    void Timer::counter()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->startTime).count();
        auto remaining = std::max(0LL, static_cast<long long>(targetDurationMs - elapsed));

        this->progress.hour = remaining / 3600000;
        this->progress.min = (remaining % 3600000) / 60000;
        this->progress.sec = (remaining % 60000) / 1000;
        this->progress.ms = remaining % 1000;

        if (progress.hour == 0 && progress.min == 0 && progress.sec == 0 && progress.ms == 0)
        { this->finished = true; }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    unsigned long long Timer::timestampToMS(Timestamp ts)
    {
        return (static_cast<unsigned long long>(ts.hour) * 3600000) + 
            (static_cast<unsigned long long>(ts.min) * 60000) + 
            (static_cast<unsigned long long>(ts.sec) * 1000) + ts.ms;
    }

    // PUBLIC
    Timer::Timer(std::string id, Timestamp duration)
        : elapsedTime(0)
    {
        this->id = id;

        this->targetDurationMs = timestampToMS(duration);
    }

    Timer::~Timer() { this->deleteTimer(); }

    void Timer::setDuration(Timestamp timer)
    { this->duration = timer; }

    std::string Timer::getID()
    { return this->id; }

    void Timer::setThread(bool toCreate)
    { this->hasThread = toCreate; }

    TimerStopwatchState Timer::getIsRunning() { return this->isRunning; };

    void Timer::start()
    {
        if (this->isRunning.load() != TRUE)
        {
            while (threadActive.load())
            { std::this_thread::sleep_for(std::chrono::milliseconds(10)); }

            this->startTime = std::chrono::high_resolution_clock::now() - elapsedTime;
            this->isRunning.store(TRUE);
            this->finished = false;

            if (hasThread)
            {
                threadActive.store(true);

                std::thread([this]() {
                    while (isRunning.load() == TRUE)
                    {
                        this->counter();

                        if (this->finished)
                        { break; }
                    }

                    threadActive.store(false);
                }).detach();
            }

            else
            {
                while (isRunning.load() == TRUE)
                {
                    this->counter();

                    if (this->finished)
                    { break; }
                }
            }
        }
    }

    void Timer::stop()
    {
        if (this->isRunning.load())
        {
            auto now = std::chrono::high_resolution_clock::now();

            elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->startTime);
        }

        this->isRunning.store(PAUSED);
    }

    void Timer::deleteTimer()
    {
        this->isRunning.store(FALSE);
        this->reset();
    }

    void Timer::reset()
    { this->progress = {0, 0, 0, 0}; }

    void Timer::set(Timestamp time)
    { this->addProgress = time; }

    Timestamp Timer::get()
    { return this->progress; }

    bool Timer::isFinished()
    { return this->finished; }
}

#endif
