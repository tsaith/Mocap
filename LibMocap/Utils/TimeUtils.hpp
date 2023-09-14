# pragma once

#include <chrono>
#include <thread>
//#include <time.h>

namespace time_utils {

    void dealy(int sec) {
        std::this_thread::sleep_for(std::chrono::seconds(sec));
    }
    void udealy(int sec) {
        std::this_thread::sleep_for(std::chrono::microseconds(sec));
    }

}
