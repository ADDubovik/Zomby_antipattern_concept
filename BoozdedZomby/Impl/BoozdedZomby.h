#pragma once

#include <memory>
#include <optional>
#include <future>

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
    ~Zomby() override;

    void run(const std::shared_ptr<Common::Listener> listener) override;

private:
    std::shared_ptr<Common::Listener> _listener;
    std::shared_ptr<boozd::azzio::stream> _stream;
    std::shared_ptr<boozd::azzio::buffer> _buffer;
    std::shared_ptr<boozd::azzio::io_context> _context;
    std::optional<std::future<void>> _futureOptional;
};
} // namespace BoozdedZomby
