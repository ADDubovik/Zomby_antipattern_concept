#include <sstream>
#include <string>

#include "SteppingZomby.h"
#include "Common/Listener.h"

namespace {
void doSomething(Common::Listener& listener, std::string&& callingFunctionName)
{
    listener.processData(std::make_shared<Common::Listener::Data>(callingFunctionName + " started\n"));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    listener.processData(std::make_shared<Common::Listener::Data>(callingFunctionName + " finished\n"));
}
} // namespace

namespace SteppingZomby {
Zomby::Zomby() = default;

std::shared_ptr<Zomby> Zomby::create()
{
    return std::shared_ptr<Zomby>(new Zomby());
}

Zomby::~Zomby()
{
    if (_semaphore && _thread.joinable()) {
        if (_thread.get_id() == std::this_thread::get_id()) {
            _thread.detach();
        } else {
            _semaphore = false;
            _thread.join();
        }
    }

    if (_listener) {
        std::ostringstream buf;
        buf << typeid(*this).name() << "::" << __func__ << std::endl;
        _listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
    }
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

    _thread = std::thread([shis = shared_from_this()](){
        if (shis && shis->_listener && shis->_semaphore) {
            shis->resolveDnsName();
        }
        if (shis && shis->_listener && shis->_semaphore) {
            shis->connectTcp();
        }
        if (shis && shis->_listener && shis->_semaphore) {
            shis->establishSsl();
        }
        if (shis && shis->_listener && shis->_semaphore) {
            shis->sendHttpRequest();
        }
        if (shis && shis->_listener && shis->_semaphore) {
            shis->readHttpReply();
        }
    });
}

void Zomby::resolveDnsName()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::connectTcp()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::establishSsl()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::sendHttpRequest()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}

void Zomby::readHttpReply()
{
    doSomething(*_listener, std::string(typeid(*this).name()) + "::" + __func__);
}
} // namespace SteppingZomby
