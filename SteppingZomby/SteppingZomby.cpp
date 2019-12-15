#include <sstream>
#include <string>

#include "SteppingZomby.h"
#include "Common/Listener.h"

namespace SteppingZomby {
Zomby::Zomby() = default;

std::shared_ptr<Zomby> Zomby::create()
{
    return std::shared_ptr<Zomby>(new Zomby());
}

Zomby::~Zomby()
{
    if (_semaphore) {
        if (std::this_thread::get_id() != _thread.get_id()) {
            auto guard = std::lock_guard(_semaphore->first);
            _semaphore->second = false;
        } else {
            _semaphore->second = false;
        }
    }

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
    // two separate lines needed because of absence of std::mutex move c-tor
    _semaphore = std::make_shared<Semaphore>();
    _semaphore->second = true;

    _thread = std::thread([listener, semaphore = _semaphore](){
        if (listener && semaphore) {
            if (resolveDnsName(*listener, *semaphore)
                    && connectTcp(*listener, *semaphore)
                    && establishSsl(*listener, *semaphore)
                    && sendHttpRequest(*listener, *semaphore)) {
                readHttpReply(*listener, *semaphore);
            }
        }
    });
}

bool Zomby::resolveDnsName(Common::Listener& listener, Semaphore& semaphore)
{
    return doSomething(listener, semaphore, __func__);
}

bool Zomby::connectTcp(Common::Listener& listener, Semaphore& semaphore)
{
    return doSomething(listener, semaphore, __func__);
}

bool Zomby::establishSsl(Common::Listener& listener, Semaphore& semaphore)
{
    return doSomething(listener, semaphore, __func__);
}

bool Zomby::sendHttpRequest(Common::Listener& listener, Semaphore& semaphore)
{
    return doSomething(listener, semaphore, __func__);
}

bool Zomby::readHttpReply(Common::Listener& listener, Semaphore& semaphore)
{
    return doSomething(listener, semaphore, __func__);
}

bool Zomby::doSomething(Common::Listener& listener, Semaphore& semaphore, std::string&& callingFunctionName)
{
    {
        auto guard = std::lock_guard(semaphore.first);
        if (!semaphore.second) {
            return false;
        }
        listener.processData(std::make_shared<Common::Listener::Data>(callingFunctionName + " started\n"));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    {
        auto guard = std::lock_guard(semaphore.first);
        if (!semaphore.second) {
            return false;
        }
        listener.processData(std::make_shared<Common::Listener::Data>(callingFunctionName + " finished\n"));
    }

    return true;
}
} // namespace SteppingZomby
