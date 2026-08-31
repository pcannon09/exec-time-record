#include <string>

#include "../inc/Stopwatch.hpp"
#include "../inc/types.hpp"

#if __cplusplus >= 201103L
#include <chrono>
#include <thread>
#include <atomic>

namespace timeUtils
{
    // PRIVATE
    void Stopwatch::counter()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->startTime).count();

        this->progress.hour = elapsed / 3600000 + addProgress.hour;
        this->progress.min = (elapsed % 3600000) / 60000 +  addProgress.min;
        this->progress.sec = (elapsed % 60000) / 1000 +  addProgress.sec;
        this->progress.ms = elapsed % 1000 +  addProgress.ms;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // PUBLIC
    Stopwatch::Stopwatch(std::string id)
        : elapsedTime(0)
    { this->id = id; }

    Stopwatch::~Stopwatch()
    {
		this->setThread(false);
		// this->
    }

    std::string Stopwatch::getID()
    { return this->id; }

    void Stopwatch::setThread(bool toCreate)
    { this->hasThread = toCreate; }

    TimerStopwatchState Stopwatch::getIsRunning() { return this->isRunning; };

    void Stopwatch::start()
    {
        if (this->isRunning.load() != TRUE)
        {
            while (threadActive.load())
            { std::this_thread::sleep_for(std::chrono::milliseconds(10)); }

            this->startTime = std::chrono::high_resolution_clock::now() - elapsedTime;
            this->isRunning.store(TRUE);

            if (hasThread)
            {
                threadActive.store(true);

                std::thread([this]() {
                    while (isRunning.load() == TRUE)
                    {
                        this->counter();
                    }

                    threadActive.store(false);
                }).detach();
            }

            else
            {
                while (isRunning.load() == TRUE)
                { this->counter(); }
            }
        }
    }

    void Stopwatch::stop()
    {
        if (this->isRunning.load())
        {
            auto now = std::chrono::high_resolution_clock::now();

            elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->startTime);
        }

        this->isRunning.store(PAUSED);
    }

    void Stopwatch::reset()
    {
		this->elapsedTime = std::chrono::milliseconds(0);
    	this->progress = {};
    }

    void Stopwatch::set(Timestamp time)
    { this->addProgress = time; }

    Timestamp Stopwatch::get()
    { return this->progress; }
}
#endif
