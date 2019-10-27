#pragma once

#include <memory>

namespace PimplCyclic {
class Cyclic
{
public:
    Cyclic();
    ~Cyclic();

private:
    class Impl;
    std::shared_ptr<Impl> _impl;
};
} // namespace PimplCyclic
