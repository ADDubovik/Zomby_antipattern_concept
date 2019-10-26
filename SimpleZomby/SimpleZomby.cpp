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
        _listener = std::move(listener);
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
        int i = 0;
        while (shis && shis->_listener && shis->_semaphore) {
            if (++i == 10) {
                shis->_listener->processData(std::make_shared<Common::Listener::Data>("SimpleZomby is alive!\n"));
                i = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
}
} // namespace SimpleZomby
