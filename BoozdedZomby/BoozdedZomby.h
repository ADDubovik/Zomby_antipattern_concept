#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "Common/Manager.h"
#include "boozd/azzio/buffer.h"
#include "boozd/azzio/io_context.h"
#include "boozd/azzio/stream.h"

namespace Common {
class Listener;
} // namespace Common
namespace boozd::azzio {
class stream;
} // namespace boozd::azzio

namespace BoozdedZomby {
class Zomby final : public Common::Manager, public std::enable_shared_from_this<Zomby>
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
    std::unique_ptr<boozd::azzio::stream> _stream;
    boozd::azzio::buffer _buffer;
    boozd::azzio::io_context _context;
    std::thread _thread;
};
} // namespace BoozdedZomby
