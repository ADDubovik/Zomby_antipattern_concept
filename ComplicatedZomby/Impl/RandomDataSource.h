#pragma once

#include <memory>
#include <atomic>
#include <future>
#include <optional>

#include "ComplicatedZomby/DataSource.h"

class RandomDataSource final : public DataSource
{
public:
    RandomDataSource();
    ~RandomDataSource() override;

    virtual void run(const std::shared_ptr<DataReceiver> receiver) override;

private:
    using Semaphore = std::atomic<bool>;
    using SemaphoreShared = std::shared_ptr<Semaphore>;

    const SemaphoreShared _semaphoreShared;
    std::optional<std::future<void>> _futureOptional;
};
