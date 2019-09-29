#pragma once

#include <string>
#include <memory>

namespace Common {
class Listener
{
public:
    virtual ~Listener() = default;

    virtual void processData(const std::shared_ptr<const std::string> data) = 0;
};
} // namespace Common
