#include <iostream>

#include "RandomDataSource.h"
#include "ComplicatedZomby/DataReceiver.h"

namespace ComplicatedZomby {
RandomDataSource::~RandomDataSource()
{
    _semaphore = false;

    _thread.detach();

    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void RandomDataSource::runOnce(const std::shared_ptr<DataReceiver> receiver)
{
    if (_semaphore) {
        throw std::runtime_error("ComplicatedZomby::RandomDataSource::runOnce() called twice");
    }

    _semaphore = true;

    _thread = std::thread([receiver, &semaphore = _semaphore](){
        while (receiver && semaphore) {
            receiver->dataArrived(rand());
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}
} // namespace ComplicatedZomby
