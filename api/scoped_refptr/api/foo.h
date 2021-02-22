#ifndef FOO_H_
#define FOO_H_

#include "ref_count_base.h"
#include "scoped_refptr.h"
#include "ref_count_object.h"

class Foo : public rtc::RefCountedBase {
    public:
        Foo();
        ~Foo();

        int getCount();
        void setCount(int count);

    private:
        int m_iCount = 0;
};

#endif
