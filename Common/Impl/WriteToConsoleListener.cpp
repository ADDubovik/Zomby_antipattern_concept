#include <iostream>

#include "WriteToConsoleListener.h"

namespace Common {
WriteToConsoleListener::~WriteToConsoleListener() = default;

void WriteToConsoleListener::processData(const std::shared_ptr<const std::string> data)
{
    if (data)
        std::cout << *data;
}
} // namespace Common