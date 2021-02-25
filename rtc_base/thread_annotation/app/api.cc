#include <iostream>
#include "api.h"
#include "foo.h"

RtcAPI::RtcAPI() {
    std::cout << "Constructing RtcAPI" << std::endl;
}

RtcAPI::~RtcAPI() {
    std::cout << "Destructing RtcAPI" << std::endl;
}

void RtcAPI::testThreadAnnotations() RTC_EXCLUSIVE_LOCKS_REQUIRED(mutex_)
{
    mutex_.lock();
    m_pFooPtr = std::unique_ptr<Foo>(new Foo());
    m_pFooPtr->testFunc();
    mutex_.unlock();
    return;
}
