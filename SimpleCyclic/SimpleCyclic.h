#pragma once

#include <memory>
#include <functional>

namespace SimpleCyclic {
class Cyclic : public std::enable_shared_from_this<Cyclic>
{
public:
    static std::shared_ptr<Cyclic> create();

    void doSomething();

private:
    Cyclic();

    std::function<void(void)> _fn;
};
} // namespace SimpleCyclic
