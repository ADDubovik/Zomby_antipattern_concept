#include <sstream>
#include <iostream>

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
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void Zomby::initWithListener(std::shared_ptr<Common::Listener> listener)
{
    if (listener && !_listener) {
        _listener = listener;
    }
}

void Zomby::run()
{
    if (!_dataSource) {
        _dataSource = std::make_shared<RandomDataSource>();
    }
    if (_dataSource) {
        _dataSource->run(shared_from_this());
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
