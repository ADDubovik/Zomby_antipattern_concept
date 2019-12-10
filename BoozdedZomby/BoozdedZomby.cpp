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
    _semaphore = false;

    if (_thread.joinable()) {
        _thread.join();
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
        throw std::runtime_error("BoozdedZomby::Zomby::runOnce() called twice");
    }

    _listener = listener;
    _semaphore = true;

    _thread = std::thread([this]() {
        while (_semaphore && _listener) {
            auto handler = [this](auto errorCode) {
                if (_listener && errorCode == boozd::azzio::io_context::error_code::no_error) {
                    std::ostringstream buf;
                    buf << "BoozdedZomby has got a fresh data: ";
                    for (auto const &elem : _buffer)
                        buf << elem << ' ';
                    buf << std::endl;

                    _listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
                }
            };
            _buffer.clear();
            _context.async_read(_stream, _buffer, handler);
            _context.run();
        }
    });
}
} // namespace BoozdedZomby
