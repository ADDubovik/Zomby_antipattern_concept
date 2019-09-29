#include <iostream>

#include "random_stream.h"

namespace boozd::azzio {
boozd::azzio::random_stream::~random_stream()
{
    std::cout << __func__ << std::endl;
}

std::optional<int> random_stream::read()
{
    if (!(rand() & 0xff))
        return rand();

    return std::nullopt;
}
} // namespace boozd::azzio
