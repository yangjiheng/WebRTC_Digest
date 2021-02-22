#include <iostream>
#include "foo.h"

using namespace std;

Foo::Foo() {
    cout << "Foo Constructor executed" << endl;
}

Foo::~Foo() {
    cout << "Foo Destructor executed" << endl;
}

int Foo::getCount()
{
    return m_iCount;
}

void Foo::setCount(int count)
{
    m_iCount = count;
}
