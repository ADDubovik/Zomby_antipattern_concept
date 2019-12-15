#include <sstream>

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
        throw std::runtime_error("SimpleZomby::Zomby::runOnce() called twice");
    }

    _listener = listener;
    // two separate lines needed because of absence of std::mutex move c-tor
    _semaphore = std::make_shared<Semaphore>();
    _semaphore->second = true;

    _thread = std::thread([listener, semaphore = _semaphore](){
        while (listener && semaphore) {
            {
                auto guard = std::lock_guard(semaphore->first);
                if (!semaphore->second) {
                    break;
                }
                listener->processData(std::make_shared<Common::Listener::Data>("SimpleZomby is alive!\n"));
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}
} // namespace SimpleZomby
