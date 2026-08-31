#include <string>

#include "../inc/Sleep.hpp"

#if __cplusplus >= 201102L
#include <chrono>
#include <thread>

namespace timeUtils
{
    Sleep::Sleep(std::string ID)
    	: id(ID)
    { this->id = ID; }

    void Sleep::hours(unsigned int duration)
    { std::this_thread::sleep_for(std::chrono::hours(duration)); }

    void Sleep::minutes(unsigned int duration)
    { std::this_thread::sleep_for(std::chrono::minutes(duration)); }

    void Sleep::seconds(unsigned int duration)
    { std::this_thread::sleep_for(std::chrono::seconds(duration)); }

    void Sleep::seconds(double duration)
    { this->milliseconds(static_cast<int>(duration * 1000)); }

    void Sleep::milliseconds(unsigned int duration)
    { std::this_thread::sleep_for(std::chrono::milliseconds(duration)); }

    void Sleep::nanoseconds(unsigned int duration)
    { std::this_thread::sleep_for(std::chrono::nanoseconds(duration)); }

    std::string Sleep::getID()
    { return this->id; }
}

#endif
