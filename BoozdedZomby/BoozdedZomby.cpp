#include <iostream>
#include <sstream>

#include "boozd/azzio/impl/random_stream.h"
#include "BoozdedZomby.h"
#include "Common/Listener.h"

namespace BoozdedZomby {
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

void Zomby::runOnce(std::shared_ptr<Common::Listener> listener)
{
    if (_semaphore && _thread.joinable()) {
        _semaphore = false;
        _thread.join();
    }

    _semaphore = true;

    _stream = std::make_unique<boozd::azzio::random_stream>();
    _thread = std::thread([shis = shared_from_this()]() {
        while (shis && shis->_semaphore && shis->_stream && shis->_listener) {
            auto handler = [shis](auto errorCode) {
                if (shis && shis->_listener && errorCode == boozd::azzio::io_context::error_code::no_error) {
                    std::ostringstream buf;
                    buf << "BoozdedZomby has got a fresh data: ";
                    for (auto const &elem : shis->_buffer)
                        buf << elem << ' ';
                    buf << std::endl;

                    shis->_listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
                }
            };
            shis->_buffer.clear();
            shis->_context.async_read(*shis->_stream, shis->_buffer, handler);
            shis->_context.run();
        }
    });
}
} // namespace BoozdedZomby
