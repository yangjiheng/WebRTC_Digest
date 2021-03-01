#include <iostream>
#include "api.h"
#include "numerics/safe_compare.h"

using namespace std;

int main(int argc, char**argv) {
    // std::unique_ptr<RtcAPI> api(new RtcAPI());
    // api->testThreadAnnotations();

    // App Module 1: Safe compare
    int num1 = 10;
    float num2 = 11.0f;

    if(rtc::SafeGt(num1, num2)) {
        std::cout << "num1 is greater than num2" << std::endl;
    }
    else {
        std::cout << "num1 is smaller than num2" << std::endl;
    }

    

    return 0;
}
