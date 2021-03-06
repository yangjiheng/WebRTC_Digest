#include <iostream>
#include "event.h"

using namespace std;

int main(int argc, char**argv) {
    std::cout << "Task Queue Demo" << std::endl;

    std::cout << "Demo 1 - Event mechanism" << std::endl;
    rtc::Event event;
    std::cout << "Let's wait 5000ms with event" << std::endl;
    if(true == event.Wait(5000)) {
        std::cout << "Event waited 5000ms" << std::endl;
    }

    std::cout << "Demo 2 - Setting event initially signaled" << std::endl;
    rtc::Event event_sec(false, true);
    if(event_sec.Wait(5000) == true) {
        std::cout << "Initially signaled" << std::endl;
    }
    else {
        std::cout << "Initially not signaled" << std::endl;
    }

    
    

    std::cout << "Demo end" << std::endl;
    return 0;
}
