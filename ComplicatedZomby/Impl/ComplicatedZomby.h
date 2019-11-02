#pragma once

#include <memory>

#include "ComplicatedZomby/DataReceiver.h"
#include "Common/Manager.h"

namespace Common {
class Listener;
} // namespace Common

namespace ComplicatedZomby {
class DataSource;

class Zomby final : public DataReceiver, public Common::Manager, public std::enable_shared_from_this<Zomby>
{
public:
    static std::shared_ptr<Zomby> create();

    ~Zomby() override;

    void runOnce(std::shared_ptr<Common::Listener> listener) override;

private:
    Zomby();

    void dataArrived(int data) override;

    std::shared_ptr<DataSource> _dataSource;
    std::shared_ptr<Common::Listener> _listener;
};
} // namespace ComplicatedZomby
