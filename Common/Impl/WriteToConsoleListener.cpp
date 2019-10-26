#include <iostream>

#include "WriteToConsoleListener.h"

namespace Common {
WriteToConsoleListener::WriteToConsoleListener() = default;

WriteToConsoleListener::~WriteToConsoleListener()
{
    auto lock = std::lock_guard(_mutex);
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

std::shared_ptr<WriteToConsoleListener> WriteToConsoleListener::instance()
{
    static auto inst = std::shared_ptr<WriteToConsoleListener>(new WriteToConsoleListener);
    return inst;
}

void WriteToConsoleListener::processData(const std::shared_ptr<const Data> data)
{
    if (data) {
        auto lock = std::lock_guard(_mutex);
        std::cout << *data << std::flush;
    }
}

} // namespace Common
