#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include <optional>
#include <condition_variable>

#include "Common/ThreadJoiner.h"

namespace Common {
class ThreadJoinerAsync final : public ThreadJoiner
{
public:
    ThreadJoinerAsync();
    ThreadJoinerAsync(const ThreadJoinerAsync&) = delete;
    ThreadJoinerAsync(ThreadJoinerAsync&&) = delete;
    ThreadJoinerAsync& operator=(const ThreadJoinerAsync&) = delete;
    ThreadJoinerAsync& operator=(ThreadJoinerAsync&&) = delete;

    ~ThreadJoinerAsync() override;

    void join(std::thread&&) override;

private:
    using Data = std::queue<std::thread>;
    using Semaphore = std::atomic<bool>;

    std::mutex _mutex;
    Data _data;
    Semaphore _semaphore;
    std::condition_variable _cv;
    std::thread _thread;

    void threadFn();
};
} // namespace Common
