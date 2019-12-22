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
    if (_thread.joinable()) {
        _thread.detach();
    }

    if (_listener) {
        std::ostringstream buf;
        buf << typeid(*this).name() << "::" << __func__ << std::endl;
        _listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
    }
}

void Zomby::runOnce(std::shared_ptr<Common::Listener> listener)
{
    if (_semaphore) {
        throw std::runtime_error("SteppingZomby::Zomby::runOnce() called twice");
    }

    _listener = listener;
    _semaphore = true;

    _thread = std::thread([whis = weak_from_this()](){
        if (auto shis = whis.lock(); shis && shis->_listener) {
            shis->resolveDnsName();
        }
        if (auto shis = whis.lock(); shis && shis->_listener) {
            shis->connectTcp();
        }
        if (auto shis = whis.lock(); shis && shis->_listener) {
            shis->establishSsl();
        }
        if (auto shis = whis.lock(); shis && shis->_listener) {
            shis->sendHttpRequest();
        }
        if (auto shis = whis.lock(); shis && shis->_listener) {
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
