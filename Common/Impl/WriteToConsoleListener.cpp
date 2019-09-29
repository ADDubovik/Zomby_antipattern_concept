#include <iostream>

#include "WriteToConsoleListener.h"

namespace Common {
WriteToConsoleListener::~WriteToConsoleListener()
{
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void WriteToConsoleListener::processData(const std::shared_ptr<const Data> data)
{
    if (data) {
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << *data << std::flush;
    }
}
} // namespace Common
