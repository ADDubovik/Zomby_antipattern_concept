#include <iostream>

#include "random_stream.h"

namespace boozd::azzio {
boozd::azzio::random_stream::~random_stream()
{
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

std::optional<int> random_stream::read()
{
    if (!(rand() & 0x1))
        return rand();

    return std::nullopt;
}
} // namespace boozd::azzio
