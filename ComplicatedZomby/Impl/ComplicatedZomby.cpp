#include <sstream>
#include <iostream>

#include "ComplicatedZomby.h"
#include "RandomDataSource.h"
#include "Common/Listener.h"

namespace ComplicatedZomby {
Zomby::~Zomby()
{
    std::cout << __func__ << std::endl;
}

void Zomby::run(const std::shared_ptr<Common::Listener> listener)
{
    _listener = listener;

    if (!_dataSource)
        _dataSource = std::make_shared<RandomDataSource>();
    if (_dataSource)
        _dataSource->run(shared_from_this());
}

void Zomby::dataArrived(int data)
{
    if (_listener) {
        std::ostringstream buf;
        buf << "ComplicatedZomby have got a fresh data: " << data << std::endl;
        _listener->processData(std::make_shared<std::string>(buf.str()));
    }
}
} // namespace ComplicatedZomby