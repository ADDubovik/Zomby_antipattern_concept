#pragma once

#include <memory>

namespace Common {
class Listener;

class Manager
{
public:
    virtual ~Manager() = default;

    virtual void initWithListener(std::shared_ptr<Common::Listener> listener) = 0;

    virtual void run() = 0;
};
} // namespace Common
