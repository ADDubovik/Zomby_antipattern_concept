#pragma once

#include <memory>

class DataReceiver;

class DataSource
{
public:
    virtual ~DataSource() = default;

    virtual void run(const std::shared_ptr<DataReceiver> receiver) = 0;
};
