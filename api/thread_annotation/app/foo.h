#ifndef FOO_H_
#define FOO_H_

#include "rtc_base/thread_annotations.h"

class RTC_LOCKABLE Foo {
    public:
        Foo();
        ~Foo();

    public:
        void testFunc();
};

#endif
