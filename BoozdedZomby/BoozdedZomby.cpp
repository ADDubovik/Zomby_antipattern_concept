#include <iostream>
#include <sstream>

#include "BoozdedZomby.h"
#include "Common/Listener.h"
#include "Common/ThreadJoiner.h"
#include "boozd/azzio/buffer.h"
#include "boozd/azzio/io_context.h"
#include "boozd/azzio/impl/random_stream.h"

namespace BoozdedZomby {
Zomby::Zomby(std::shared_ptr<Common::ThreadJoiner> joiner)
    : _joiner(joiner)
{
    if (!_joiner) {
        throw std::runtime_error("An empty joiner in BoozdedZomby::Zomby::Zomby");
    }
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
        _joiner->join(std::move(_thread));
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
    // two separate lines needed because of absence of std::mutex move c-tor
    _semaphore = std::make_shared<Semaphore>();
    _semaphore->second = true;

    _thread = std::thread([listener, semaphore = _semaphore](){
        if (listener && semaphore) {
            boozd::azzio::random_stream stream;
            boozd::azzio::buffer buffer;
            boozd::azzio::io_context context;

            auto handler = [&listener, &semaphore, &buffer](auto errorCode) {
                auto guard = std::lock_guard(semaphore->first);
                if (semaphore->second && errorCode == boozd::azzio::io_context::error_code::no_error) {
                    std::ostringstream buf;
                    buf << "BoozdedZomby has got a fresh data: ";
                    for (auto const &elem : buffer)
                        buf << elem << ' ';
                    buf << std::endl;

                    listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
                }
            };

            while (true) {
                {
                    auto guard = std::lock_guard(semaphore->first);
                    if (!semaphore->second) {
                        break;
                    }
                }
                buffer.clear();
                context.async_read(stream, buffer, handler);
                context.run();
            }
        }
    });
}
} // namespace BoozdedZomby
