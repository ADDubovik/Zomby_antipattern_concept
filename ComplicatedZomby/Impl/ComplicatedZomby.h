#pragma once

#include <memory>

#include "ComplicatedZomby/DataReceiver.h"
#include "ComplicatedZomby/Manager.h"

namespace Common {
class Listener;
} // namespace Common

namespace ComplicatedZomby {
class DataSource;

class Zomby final : public DataReceiver, public Manager, public std::enable_shared_from_this<Zomby>
{
public:
    ~Zomby() override;

    void run(const std::shared_ptr<Common::Listener> listener) override;

private:
    virtual void dataArrived(int data) override;

    std::shared_ptr<DataSource> _dataSource;
    std::shared_ptr<Common::Listener> _listener;
};
} // namespace ComplicatedZomby
