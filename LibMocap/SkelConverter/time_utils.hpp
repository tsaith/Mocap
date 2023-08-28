#ifndef TIME_UTILS_HPP
#define TIME_UTILS_HPP 

#include <time.h>

namespace time_utils {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    void dealy(int sec) {
        std::this_thread::sleep_for(std::chrono::seconds(sec));
    }
    void udealy(int sec) {
        std::this_thread::sleep_for(std::chrono::microseconds(sec));
    }
#else
    #include <unistd.h>
    void dealy(int sec) {
        sleep(sec);
    }
    void udealy(int sec) {
        usleep(sec);
    }
#endif
}

#endif // TIME_UTILS_HPP