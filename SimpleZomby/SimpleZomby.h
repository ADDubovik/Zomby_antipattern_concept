#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "Common/Manager.h"

namespace Common {
class Listener;
} // namespace Common

namespace SimpleZomby {
class Zomby final : public Common::Manager
{
public:
    static std::shared_ptr<Zomby> create();

    ~Zomby() override;

    void runOnce(std::shared_ptr<Common::Listener> listener) override;

private:
    Zomby();

    using Semaphore = std::pair<std::mutex, bool>;

    std::shared_ptr<Common::Listener> _listener;
    std::shared_ptr<Semaphore> _semaphore;
    std::thread _thread;
};
} // namespace SimpleZomby
