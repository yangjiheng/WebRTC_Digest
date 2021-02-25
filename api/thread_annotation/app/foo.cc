#include <iostream>
#include "foo.h"

using namespace std;

Foo::Foo() {
    std::cout << "Constructing Foo " << std::endl;
}

Foo::~Foo() {
    std::cout << "Destructing Foo " << std::endl;
}

void Foo::testFunc()
{
    std::cout << "Foo test func" << std::endl;
}
