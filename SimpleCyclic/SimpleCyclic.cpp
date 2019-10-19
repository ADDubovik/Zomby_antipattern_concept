#include "SimpleCyclic.h"

#include <iostream>


namespace SimpleCyclic {
Cyclic::Cyclic() = default;

Cyclic::~Cyclic()
{
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

std::shared_ptr<Cyclic> Cyclic::create()
{
    return std::shared_ptr<Cyclic>(new Cyclic);
}

void Cyclic::doSomething()
{
    _fn = [shis = shared_from_this()](){};
}
} // namespace SimpleCyclic
