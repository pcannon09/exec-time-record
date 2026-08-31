#include <iostream>

#include "../../inc/Stopwatch.hpp"

#if __cplusplus >= 201102L
#include <chrono>
#include <thread>

namespace tests
{
    int stopwatch()
    {
        std::cout << "Starting at 1min, 9secs\n";

        timeUtils::Stopwatch watch("main");

        watch.setThread(true);
        watch.set({0, 1, 9, 0});
        watch.start();

        std::thread watchT([&watch]() {
            while (1)
            {
                std::cout << watch.get().hour;
                std::cout << " : " << watch.get().min;
                std::cout << " : " << watch.get().sec;
                std::cout << " : " << watch.get().ms << "\r" << std::flush;
            }
        });

        watchT.detach();

        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "\nSTOP\n";

        watch.stop();

        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "\nSTART\n";

        watch.start();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        return 0;
    }
}

#else
namespace tests
{ int stopwatch() { return -1; } }

#endif

