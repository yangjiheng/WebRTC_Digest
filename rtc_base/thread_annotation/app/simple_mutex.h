#ifndef SIMPLE_MUTEX_H_
#define SIMPLE_MUTEX_H_

#include <iostream>
#include "thread_annotations.h"

typedef std::mutex __attribute__((capability("mutex"))) Mutex;

class RTC_LOCKABLE SimpleMutex {
public:
    SimpleMutex() = default;
    SimpleMutex(const SimpleMutex&) = delete;
    SimpleMutex& operator=(const SimpleMutex&) = delete;

    void lock() {
        mutex_.lock();
    }

    void unlock() {
        mutex_.unlock();
    }

private:
    mutable Mutex mutex_;
};


#endif
