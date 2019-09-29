#include <iostream>

#include "RandomDataSource.h"
#include "ComplicatedZomby/DataReceiver.h"

namespace ComplicatedZomby {
RandomDataSource::~RandomDataSource()
{
    if (_semaphoreShared) {
        *_semaphoreShared = false;
        while (_semaphoreShared.use_count() > 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void RandomDataSource::run(const std::shared_ptr<DataReceiver> receiver)
{
    if (_semaphoreShared) {
        *_semaphoreShared = false;
        while (_semaphoreShared.use_count() > 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    _semaphoreShared = std::make_shared<Semaphore>(true);

    _thread = std::thread([receiver, semaphoreShared = _semaphoreShared](){
        while (receiver && semaphoreShared && *semaphoreShared) {
            receiver->dataArrived(rand());
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });

    _thread.detach();
}
} // namespace ComplicatedZomby
