#pragma once

#include <memory>

namespace Common {
class Listener;

class Manager
{
public:
    Manager() = default;
    Manager(const Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(const Manager&) = delete;
    Manager& operator=(Manager&&) = delete;

    virtual ~Manager() = default;

    virtual void runOnce(std::shared_ptr<Common::Listener> listener) = 0;
};
} // namespace Common
