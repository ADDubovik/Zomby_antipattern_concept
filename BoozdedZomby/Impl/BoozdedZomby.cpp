#include <iostream>
#include <sstream>

#include "boozd/azzio/impl/random_stream.h"
#include "BoozdedZomby.h"
#include "Common/Listener.h"

namespace BoozdedZomby {
Zomby::Zomby()
    : _semaphoreShared(std::make_shared<Semaphore>(false))
{
}

Zomby::~Zomby()
{
    if (_semaphoreShared)
        *_semaphoreShared = false;

    std::cout << __func__ << std::endl;
} // ... and waiting for future destruction

void Zomby::run(const std::shared_ptr<Common::Listener> listener)
{
    if (_semaphoreShared) {
        *_semaphoreShared = false;
        _futureOptional.reset(); // waiting for future destruction

        *_semaphoreShared = true;

        _listener = listener;
        _stream = std::make_shared<boozd::azzio::random_stream>();
        _buffer = std::make_shared<boozd::azzio::buffer>();
        _context = std::make_shared<boozd::azzio::io_context>();
        _futureOptional = std::async(std::launch::async, [shis = shared_from_this()]() {
            while (shis && shis->_semaphoreShared && *shis->_semaphoreShared && shis->_buffer && shis->_stream && shis->_context && shis->_listener) {
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
}
} // namespace BoozdedZomby
