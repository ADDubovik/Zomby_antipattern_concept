#include <iostream>
#include <sstream>

#include "boozd/azzio/impl/random_stream.h"
#include "BoozdedZomby.h"
#include "Common/Listener.h"

namespace BoozdedZomby {
Zomby::~Zomby()
{
    std::cout << __func__ << std::endl;
} // ... and waiting for future destruction

void Zomby::run(const std::shared_ptr<Common::Listener> listener)
{
    _futureOptional.reset(); // waiting for future destruction

    _listener = listener;
    _stream = std::make_shared<boozd::azzio::random_stream>();
    _buffer = std::make_shared<boozd::azzio::buffer>();
    _context = std::make_shared<boozd::azzio::io_context>();
    _futureOptional = std::async(std::launch::async, [shis = shared_from_this()](){
        if (shis && shis->_buffer && shis->_stream && shis->_context && shis->_listener) {
            auto handler = [shis](auto errorCode) {
                if (shis && shis->_listener && shis->_buffer && errorCode == boozd::azzio::io_context::error_code::no_error)
                {
                    std::ostringstream buf;
                    buf << "BoozdedZomby has got data: ";
                    for (auto const &elem : *shis->_buffer)
                        buf << elem;
                    buf << std::endl;

                    shis->_listener->processData(std::make_shared<std::string>(buf.str()));
                }
            };
            shis->_context->async_read(*shis->_buffer, *shis->_stream, handler);
            shis->_context->run();
        }
    });
}
} // namespace BoozdedZomby