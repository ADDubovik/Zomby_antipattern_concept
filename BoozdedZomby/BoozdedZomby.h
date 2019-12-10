#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "Common/Manager.h"
#include "boozd/azzio/buffer.h"
#include "boozd/azzio/io_context.h"
#include "boozd/azzio/impl/random_stream.h"

namespace Common {
class Listener;
} // namespace Common

namespace BoozdedZomby {
class Zomby final : public Common::Manager
{
public:
    static std::shared_ptr<Zomby> create();

    ~Zomby() override;

    void runOnce(std::shared_ptr<Common::Listener> listener) override;

private:
    Zomby();

    using Semaphore = std::atomic<bool>;

    Semaphore _semaphore = false;
    std::shared_ptr<Common::Listener> _listener;
    boozd::azzio::random_stream _stream;
    boozd::azzio::buffer _buffer;
    boozd::azzio::io_context _context;
    std::thread _thread;
};
} // namespace BoozdedZomby
