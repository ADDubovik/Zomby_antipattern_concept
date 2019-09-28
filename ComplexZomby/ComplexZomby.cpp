#include <sstream>

#include "ComplexZomby.h"
#include "RandomDataSource.h"
#include "Listener.h"

ComplexZomby::~ComplexZomby() = default;

void ComplexZomby::run(const std::shared_ptr<Listener> listener)
{
    _listener = listener;

    if (!_dataSource)
        _dataSource = std::make_shared<RandomDataSource>();
    if (_dataSource)
        _dataSource->run(shared_from_this());
}

void ComplexZomby::dataArrived(int data)
{
    if (_listener) {
        std::ostringstream buf;
        buf << "ComplexZomby have got a fresh data: " << data << std::endl;
        _listener->processData(std::make_shared<std::string>(buf.str()));
    }
}
