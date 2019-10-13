#pragma once

#include <memory>
#include <atomic>
#include <thread>

#include "ComplicatedZomby/DataSource.h"

namespace ComplicatedZomby {
class RandomDataSource final : public DataSource
{
public:
    ~RandomDataSource() override;

    void run(const std::shared_ptr<DataReceiver> receiver) override;

private:
    using Semaphore = std::atomic<bool>;

    Semaphore _semaphore = false;
    std::thread _thread;
};
} // namespace ComplicatedZomby
