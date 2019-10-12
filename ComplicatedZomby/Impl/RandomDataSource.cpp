#include <iostream>

#include "RandomDataSource.h"
#include "ComplicatedZomby/DataReceiver.h"

namespace ComplicatedZomby {
RandomDataSource::~RandomDataSource()
{
    if (_semaphore && _thread.joinable()) {
        _semaphore = false;
        _thread.join();
    }

    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void RandomDataSource::run(const std::shared_ptr<DataReceiver> receiver)
{
    if (_semaphore && _thread.joinable()) {
        _semaphore = false;
        _thread.join();
    }

    _semaphore = true;

    _thread = std::thread([receiver, &semaphore = _semaphore](){
        int i = 0;
        while (receiver && semaphore) {
            if (++i == 1000) {
                receiver->dataArrived(rand());
                i = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
}
} // namespace ComplicatedZomby
