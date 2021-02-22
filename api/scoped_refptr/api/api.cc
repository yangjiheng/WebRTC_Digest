#include <iostream>
#include "api.h"
#include "scoped_refptr.h"
#include "foo.h"

int RtcAPI::verify_scoped_refptr()
{
    rtc::scoped_refptr<Foo> foo = new Foo();
    foo->setCount(10);
    return foo->getCount();
}

int RtcAPI::verify_shared_ptr()
{
    std::shared_ptr<Foo> foo = std::make_shared<Foo>();
    foo->setCount(100);
    return foo->getCount();
}
