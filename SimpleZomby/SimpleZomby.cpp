#include <iostream>

#include "SimpleZomby.h"
#include "Common/Listener.h"

SimpleZomby::~SimpleZomby()
{
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;

    if (_semaphoreShared) {
        *_semaphoreShared = false;
        while (_semaphoreShared.use_count() > 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void SimpleZomby::run(const std::shared_ptr<Common::Listener> listener)
{
    if (_semaphoreShared) {
        *_semaphoreShared = false;
        while (_semaphoreShared.use_count() > 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    _semaphoreShared = std::make_shared<Semaphore>(true);

    _thread = std::thread([shis = shared_from_this(), listener, semaphoreShared = _semaphoreShared](){
        while(shis && shis.use_count() > 1 && listener && semaphoreShared && *semaphoreShared) {
            listener->processData(std::make_shared<Common::Listener::Data>("SimpleZomby is alive!\n"));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });

    _thread.detach();
}
