#include <iostream>
#include "api.h"
#include "foo.h"

RtcAPI::RtcAPI() {
    std::cout << "Constructing RtcAPI" << std::endl;
}

RtcAPI::~RtcAPI() {
    std::cout << "Destructing RtcAPI" << std::endl;
}

void RtcAPI::testThreadAnnotations()
{
    return;
}
