#include "SimpleZomby.h"

#include <iostream>

void SimpleZomby::runSomethingAsync()
{
    _future = std::async(std::launch::async, [shis = shared_from_this()](){
        while(shis) {
            std::cout << "Zomby is alive!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });
}
