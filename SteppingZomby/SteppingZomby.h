#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "Common/Manager.h"

namespace Common {
class Listener;
} // namespace Common

namespace SteppingZomby {
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

    static bool resolveDnsName(Common::Listener&, Semaphore&);
    static bool connectTcp(Common::Listener&, Semaphore&);
    static bool establishSsl(Common::Listener&, Semaphore&);
    static bool sendHttpRequest(Common::Listener&, Semaphore&);
    static bool readHttpReply(Common::Listener&, Semaphore&);

    static bool doSomething(Common::Listener&, Semaphore&, std::string&&);
};
} // namespace SteppingZomby
