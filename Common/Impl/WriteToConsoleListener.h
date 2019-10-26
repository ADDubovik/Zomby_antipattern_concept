#pragma once

#include <mutex>

#include "Common/Listener.h"

namespace Common {
class WriteToConsoleListener final : public Listener
{
public:
    WriteToConsoleListener(const WriteToConsoleListener&) = delete;
    WriteToConsoleListener(WriteToConsoleListener&&) = delete;
    WriteToConsoleListener& operator=(const WriteToConsoleListener&) = delete;
    WriteToConsoleListener& operator=(WriteToConsoleListener&&) = delete;

    ~WriteToConsoleListener() override;

    static std::shared_ptr<WriteToConsoleListener> instance();

    // blocking
    void processData(const std::shared_ptr<const Data> data) override;

private:
    WriteToConsoleListener();

    std::mutex _mutex;
};
} // namespace Common
