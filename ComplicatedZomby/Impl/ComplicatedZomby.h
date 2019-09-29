#pragma once

#include <memory>

#include "ComplicatedZomby/DataReceiver.h"

class Listener;
class DataSource;

class ComplicatedZomby final : public DataReceiver, public std::enable_shared_from_this<ComplicatedZomby>
{
public:
    ~ComplicatedZomby() override;

    void run(const std::shared_ptr<Listener> listener);

private:
    virtual void dataArrived(int data) override;

    std::shared_ptr<DataSource> _dataSource;
    std::shared_ptr<Listener> _listener;
};
