#pragma once

#include <mutex>

#include "Common/Listener.h"

namespace Common {
class WriteToConsoleListener final : public Listener
{
public:
    ~WriteToConsoleListener() override;

    void processData(const std::shared_ptr<const Data> data) override;

private:
    std::mutex _mutex;
};
} // namespace Common
