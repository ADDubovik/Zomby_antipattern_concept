#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "Common/Manager.h"

namespace Common {
class Listener;
} // namespace Common

namespace SimpleZomby {
class Zomby : public Common::Manager, public std::enable_shared_from_this<Zomby>
{
public:
    ~Zomby() override;

    void run(const std::shared_ptr<Common::Listener> listener) override;

private:
    using Semaphore = std::atomic<bool>;
    using SemaphoreShared = std::shared_ptr<Semaphore>;

    SemaphoreShared _semaphoreShared;
    std::thread _thread;
};
} // namespace SimpleZomby
