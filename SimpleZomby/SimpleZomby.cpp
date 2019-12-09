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
    _semaphore = false;

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
    _semaphore = true;

    _thread = std::thread([whis = weak_from_this()](){
        while (true) {
            if (auto shis = whis.lock(); shis && shis->_listener) {
                shis->_listener->processData(std::make_shared<Common::Listener::Data>("SimpleZomby is alive!\n"));
            } else {
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}
} // namespace SimpleZomby
