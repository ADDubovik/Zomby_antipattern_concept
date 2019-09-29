#pragma once

#include "boozd/azzio/stream.h"

namespace boozd::azzio {
class random_stream final : public stream
{
public:
    ~random_stream() override;

    std::optional<int> read() override;
};
} // namespace boozd::azzio
