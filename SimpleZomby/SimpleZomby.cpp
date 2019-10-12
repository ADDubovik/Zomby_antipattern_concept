#include <iostream>

#include "SimpleZomby.h"
#include "Common/Listener.h"

namespace SimpleZomby {
std::shared_ptr<Zomby> Zomby::create()
{
    return std::shared_ptr<Zomby>(new Zomby());
}

Zomby::Zomby() = default;

Zomby::~Zomby()
{
    if (_semaphore && _thread.joinable()) {
        _semaphore = false;
        _thread.join();
    }

    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void Zomby::initWithListener(std::shared_ptr<Common::Listener> listener)
{
    if (listener && !_listener) {
        _listener = listener;
    }
}

void Zomby::run()
{
    if (_semaphore && _thread.joinable()) {
        _semaphore = false;
        _thread.join();
    }

    _semaphore = true;

    _thread = std::thread([shis = shared_from_this(), &semaphore = _semaphore](){
        int i = 0;
        while(shis && shis->_listener && semaphore) {
            if (++i == 1000) {
                shis->_listener->processData(std::make_shared<Common::Listener::Data>("SimpleZomby      is alive!\n"));
                i = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
}
} // namespace SimpleZomby
