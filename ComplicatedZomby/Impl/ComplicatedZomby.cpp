#include <sstream>

#include "ComplicatedZomby.h"
#include "RandomDataSource.h"
#include "Common/Listener.h"

namespace ComplicatedZomby {
Zomby::Zomby() = default;

std::shared_ptr<Zomby> Zomby::create()
{
    return std::shared_ptr<Zomby>(new Zomby());
}

Zomby::~Zomby()
{
    if (_listener) {
        std::ostringstream buf;
        buf << typeid(*this).name() << "::" << __func__ << std::endl;
        _listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
    }
}

void Zomby::runOnce(std::shared_ptr<Common::Listener> listener)
{
    _listener = listener;

    if (_dataSource) {
        throw std::runtime_error("ComplicatedZomby::Zomby::runOnce() called twice");
    }

    _dataSource = std::make_shared<RandomDataSource>();
    if (_dataSource) {
        _dataSource->runOnce(shared_from_this());
    }
}

void Zomby::dataArrived(int data)
{
    if (_listener) {
        std::ostringstream buf;
        buf << "ComplicatedZomby has got a fresh data: " << data << std::endl;
        _listener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
    }
}
} // namespace ComplicatedZomby
