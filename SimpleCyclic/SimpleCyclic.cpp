#include "SimpleCyclic.h"


namespace SimpleCyclic {
Cyclic::Cyclic() = default;

std::shared_ptr<Cyclic> Cyclic::create()
{
    return std::shared_ptr<Cyclic>(new Cyclic);
}

void Cyclic::doSomething()
{
    _fn = [shis = shared_from_this()](){};
}
} // namespace SimpleCyclic
