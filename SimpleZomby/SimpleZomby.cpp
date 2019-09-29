#include <iostream>

#include "SimpleZomby.h"
#include "Common/Listener.h"

SimpleZomby::~SimpleZomby()
{
    std::cout << __func__ << std::endl;
}

void SimpleZomby::run(const std::shared_ptr<Common::Listener> listener)
{
    _future = std::async(std::launch::async, [shis = shared_from_this(), listener](){
        while(shis && listener) {
            listener->processData(std::make_shared<Common::Listener::Data>("SimpleZomby is alive!\n"));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });
}
