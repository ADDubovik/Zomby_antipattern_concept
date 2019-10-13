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

    _stream = std::make_shared<boozd::azzio::random_stream>();
    _buffer = std::make_shared<boozd::azzio::buffer>();
    _context = std::make_shared<boozd::azzio::io_context>();
    _thread = std::thread([shis = shared_from_this()]() {
        while (shis && shis->_semaphore && shis->_buffer && shis->_stream && shis->_context && shis->_listener) {
            auto handler = [shis](auto errorCode) {
                if (shis && shis->_listener && shis->_buffer && errorCode == boozd::azzio::io_context::error_code::no_error) {
                    std::ostringstream buf;
                    buf << "BoozdedZomby     has got a fresh data: ";
                    for (auto const &elem : *shis->_buffer)
                        buf << elem << ' ';
                    buf << std::endl;

                    shis->_listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
                }
            };
            shis->_buffer->clear();
            shis->_context->async_read(*shis->_buffer, *shis->_stream, handler);
            shis->_context->run();
        }
    });
}
} // namespace BoozdedZomby
