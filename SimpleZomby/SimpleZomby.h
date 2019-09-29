#pragma once

#include <memory>
#include <atomic>
#include <thread>

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
    using Semaphore = std::atomic<bool>;
    using SemaphoreShared = std::shared_ptr<Semaphore>;

    SemaphoreShared _semaphoreShared;
    std::thread _thread;
};
