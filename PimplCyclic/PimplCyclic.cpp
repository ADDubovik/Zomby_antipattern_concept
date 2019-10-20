#include <iostream>
#include <functional>

#include "PimplCyclic.h"

namespace PimplCyclic {

class Cyclic::Impl : public std::enable_shared_from_this<Cyclic::Impl>
{
public:
    ~Impl()
    {
        std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
    }

    void doSomething()
    {
        _fn = [shis = shared_from_this()](){};
    }

private:
    std::function<void(void)> _fn;
};

Cyclic::Cyclic()
    : _impl(std::make_shared<Impl>())
{
}

Cyclic::~Cyclic()
{
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void Cyclic::doSomething()
{
    if (_impl) {
        _impl->doSomething();
    }
}
} // namespace PimplCyclic
