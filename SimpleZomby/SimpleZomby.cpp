#include "SimpleZomby.h"

#include <iostream>

SimpleZomby::~SimpleZomby()
{
    std::cout << __func__ << std::endl;
}

void SimpleZomby::runSomethingAsync()
{
    _future = std::async(std::launch::async, [shis = shared_from_this()](){
        while(shis) {
            std::cout << "SimpleZomby is alive!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });
}
