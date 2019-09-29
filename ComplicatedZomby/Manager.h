#pragma once

#include <memory>

namespace Common {
class Listener;
} // namespace Common

namespace ComplicatedZomby {
class Manager
{
public:
    virtual ~Manager() = default;

    virtual void run(const std::shared_ptr<Common::Listener> listener) = 0;
};
} // namespace ComplicatedZomby
