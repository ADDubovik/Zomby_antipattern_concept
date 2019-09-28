#pragma once

#include <memory>

#include "DataReceiver.h"

class Listener;
class DataSource;

class ComplexZomby final : public DataReceiver, public std::enable_shared_from_this<ComplexZomby>
{
public:
    ~ComplexZomby() override;

    void run(const std::shared_ptr<Listener> listener);

private:
    virtual void dataArrived(int data) override;

    std::shared_ptr<DataSource> _dataSource;
    std::shared_ptr<Listener> _listener;
};
