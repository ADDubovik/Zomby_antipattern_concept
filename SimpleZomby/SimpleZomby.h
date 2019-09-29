#pragma once

#include <future>

#include "Common/Manager.h"

namespace Common {
class Listener;
} // namespace Common

class SimpleZomby : public Common::Manager, public std::enable_shared_from_this<SimpleZomby>
{
public:
    ~SimpleZomby() override;

    void run(const std::shared_ptr<Common::Listener> listener) override;

private:
    std::future<void> _future;
};
