#include <iostream>
#include <string>

#include "SteppingZomby.h"
#include "Common/Listener.h"

namespace {
void doSomething(Common::Listener &listener, std::string callingFunctionName)
{
    listener.processData(std::make_shared<Common::Listener::Data>(callingFunctionName + " started\n"));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    listener.processData(std::make_shared<Common::Listener::Data>(callingFunctionName + " finished\n"));
}
} // namespace

namespace SteppingZomby {
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
        if (shis && shis->_listener && semaphore) {
            shis->prepare();
            shis->initialize();
            shis->calculate();
            shis->validate();
            shis->sendResults();
            shis->cleanup();
            shis->finalize();
        }
    });
}

void Zomby::prepare()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::initialize()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::calculate()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::validate()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::sendResults()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::cleanup()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::finalize()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}
} // namespace SteppingZomby
