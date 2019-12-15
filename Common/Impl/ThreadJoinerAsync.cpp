#include "ThreadJoinerAsync.h"

namespace Common {
ThreadJoinerAsync::ThreadJoinerAsync()
    : _semaphore(true)
    , _thread(&ThreadJoinerAsync::threadFn, this)
{
}

ThreadJoinerAsync::~ThreadJoinerAsync()
{
    _semaphore = false;
    _cv.notify_one();

    if (_thread.joinable()) {
        _thread.join();
    }
}

void ThreadJoinerAsync::join(std::thread&& thread)
{
    {
        auto lock = std::lock_guard(_mutex);
        _data.push(std::move(thread));
    }

    _cv.notify_one();
}

void ThreadJoinerAsync::threadFn()
{
    while (true) {
        auto lock = std::unique_lock(_mutex);
        _cv.wait(lock, [this](){ return !_semaphore || !_data.empty(); });

        if (!_semaphore && _data.empty()) {
            return;
        }

        auto threadToJoin = std::move(_data.front());
        _data.pop();

        lock.unlock();

        if (threadToJoin.joinable()) {
            threadToJoin.join();
        }
    }
}
} // namespace Common
