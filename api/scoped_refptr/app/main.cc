#include <iostream>
#include "scoped_refptr.h"
#include "api.h"

using namespace std;

int main(int argc, char**argv) {
    RtcAPI api;

    cout << api.verify_scoped_refptr() << endl;
    cout << api.verify_shared_ptr() << endl;

    return 0;
}
