#pragma once

#include <memory>

namespace ComplicatedZomby {
class DataReceiver;

class DataSource
{
public:
    virtual ~DataSource() = default;

    virtual void runOnce(const std::shared_ptr<DataReceiver> receiver) = 0;
};
} // namespace ComplicatedZomby
