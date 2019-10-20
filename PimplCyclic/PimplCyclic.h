#pragma once

#include <memory>
#include <functional>

namespace PimplCyclic {
class Cyclic
{
public:
    Cyclic();
    ~Cyclic();

    void doSomething();

private:
    class Impl;
    std::shared_ptr<Impl> _impl;
};
} // namespace PimplCyclic
