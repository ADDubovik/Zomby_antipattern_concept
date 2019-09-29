#pragma once

#include <string>
#include <memory>

namespace Common {
class Listener
{
public:
    virtual ~Listener() = default;

    using Data = std::string;

    virtual void processData(const std::shared_ptr<const Data> data) = 0;
};
} // namespace Common
