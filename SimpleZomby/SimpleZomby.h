#pragma once

#include <future>

class SimpleZomby : public std::enable_shared_from_this<SimpleZomby>
{
public:
    void runSomethingAsync();

private:
    std::future<void> _future;
};
