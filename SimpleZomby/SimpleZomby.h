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
    static std::shared_ptr<Zomby> create();

    ~Zomby() override;

    void initWithListener(std::shared_ptr<Common::Listener> listener) override;

    void run() override;

private:
    Zomby();

    using Semaphore = std::atomic<bool>;

    std::shared_ptr<Common::Listener> _listener;
    Semaphore _semaphore = false;
    std::thread _thread;
};
} // namespace SimpleZomby
