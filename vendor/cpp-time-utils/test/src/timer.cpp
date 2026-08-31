#include <iostream>

#include "../../inc/Timer.hpp"

#if __cplusplus >= 201102L
#include <chrono>
#include <thread>

namespace tests
{
    int timer()
    {
        std::cout << "Starting timer\n";

        timeUtils::Timer timer("main", {0, 0, 6, 0});

        timer.setThread(true);
        timer.start();

        std::thread watchT([&timer]() {
            while (1)
            {
                std::cout << timer.get().hour;
                std::cout << " : " << timer.get().min;
                std::cout << " : " << timer.get().sec;
                std::cout << " : " << timer.get().ms << "\r" << std::flush;
            }
        });

        watchT.detach();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "PAUSE\n";
        timer.stop();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "START\n";
        timer.start();

        while (!timer.isFinished()) {  }

        std::cout << timer.get().hour;
        std::cout << " : " << timer.get().min;
        std::cout << " : " << timer.get().sec;
        std::cout << " : " << timer.get().ms << "\n";

        return 0;
    }
}

#else
namespace tests
{ int timer() { return -1; } }

#endif
