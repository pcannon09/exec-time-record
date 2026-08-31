#include <iostream>

#include "../../test/inc/tests.hpp"

int main(int argc, char *argv[])
{
    std::string answer;

    if (argc > 1)
    { answer = argv[1]; }

    else
    {
        std::cout << "What test do you want to run? Timer (timer), time (time), stopwatch (stopwatch) or sleep counter (sleep)\n>>> ";
        std::cin >> answer;
    }

    if (answer == "stopwatch")
    {
        std::cout << "Starting **Stopwatch** test\n";

        return tests::stopwatch();
    }

    else if (answer == "timer")
    {
        std::cout << "Starting **Timer** test\n";

        return tests::timer();
    }

    else if (answer == "time")
    {
        std::cout << "Starting **Time** test\n";

        return tests::time();
    }

    else if (answer == "sleep")
    {
        std::cout << "Starting **Sleep** test\n";

        return tests::sleep();
    }

    else 
    {
        std::cerr << "Unknown test\n";

        return -1;
    }

    return 0;
}

