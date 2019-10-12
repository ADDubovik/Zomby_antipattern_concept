#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "Common/Manager.h"

namespace Common {
class Listener;
} // namespace Common

namespace SteppingZomby {
class Zomby : public Common::Manager, public std::enable_shared_from_this<Zomby>
{
public:
    ~Zomby() override;

    void initWithListener(std::shared_ptr<Common::Listener> listener) override;

    void run() override;

private:
    using Semaphore = std::atomic<bool>;

    std::shared_ptr<Common::Listener> _listener;
    Semaphore _semaphore;
    std::thread _thread;

    void prepare();
    void initialize();
    void calculate();
    void validate();
    void sendResults();
    void cleanup();
    void finalize();
};
} // namespace SteppingZomby
