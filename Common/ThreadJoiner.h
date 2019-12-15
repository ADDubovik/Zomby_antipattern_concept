#pragma once

#include <thread>

namespace Common {
class ThreadJoiner
{
public:
    ThreadJoiner() = default;
    ThreadJoiner(const ThreadJoiner&) = delete;
    ThreadJoiner(ThreadJoiner&&) = delete;
    ThreadJoiner& operator=(const ThreadJoiner&) = delete;
    ThreadJoiner& operator=(ThreadJoiner&&) = delete;

    virtual ~ThreadJoiner() = default;

    virtual void join(std::thread&&) = 0;
};
} // namespace Common
