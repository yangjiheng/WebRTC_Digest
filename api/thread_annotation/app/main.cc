#include <iostream>
#include "api.h"

using namespace std;

int main(int argc, char**argv) {
    std::unique_ptr<RtcAPI> api(new RtcAPI());
    api->testThreadAnnotations();
    return 0;
}
