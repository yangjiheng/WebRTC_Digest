#ifndef _API_API_H_
#define _API_API_H_

#include "ref_count_base.h"
#include "scoped_refptr.h"

class Foo;
class RtcAPI : public rtc::RefCountedBase {
public:
    RtcAPI() {}
    ~RtcAPI() {}

public:
    int verify_scoped_refptr();
    int verify_shared_ptr();
};

#endif
