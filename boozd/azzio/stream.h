#pragma once

#include <optional>

namespace boozd::azzio {
class stream
{
public:
    virtual ~stream() = default;

    virtual std::optional<int> read() = 0;
};
} // namespace boozd::azzio
