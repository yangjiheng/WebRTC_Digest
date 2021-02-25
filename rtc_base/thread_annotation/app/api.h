#ifndef _API_API_H_
#define _API_API_H_

#include "foo.h"
#include "simple_mutex.h"

class RtcAPI {
public:
    RtcAPI();
    ~RtcAPI();

public:
    void testThreadAnnotations();

private:
    SimpleMutex mutex_;
    std::unique_ptr<Foo> m_pFooPtr RTC_GUARDED_BY(mutex_);
};

#endif
