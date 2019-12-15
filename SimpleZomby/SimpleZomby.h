#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "Common/Manager.h"

namespace Common {
class Listener;
class ThreadJoiner;
} // namespace Common

namespace SimpleZomby {
class Zomby final : public Common::Manager
{
public:
    Zomby(std::shared_ptr<Common::ThreadJoiner>);

    ~Zomby() override;

    void runOnce(std::shared_ptr<Common::Listener> listener) override;

private:

    using Semaphore = std::pair<std::mutex, bool>;

    std::shared_ptr<Common::Listener> _listener;
    std::shared_ptr<Semaphore> _semaphore;
    std::thread _thread;
    const std::shared_ptr<Common::ThreadJoiner> _joiner;
};
} // namespace SimpleZomby
