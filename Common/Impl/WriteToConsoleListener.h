#pragma once

#include "Common/Listener.h"

namespace Common {
class WriteToConsoleListener final : public Listener
{
public:
    ~WriteToConsoleListener() override;

    void processData(const std::shared_ptr<const std::string> data) override;
};
} // namespace Common
