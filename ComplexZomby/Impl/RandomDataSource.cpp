#include <iostream>

#include "RandomDataSource.h"
#include "ComplexZomby/DataReceiver.h"

RandomDataSource::RandomDataSource()
    : _semaphoreShared(std::make_shared<Semaphore>(false))
{
}

RandomDataSource::~RandomDataSource()
{
    if (_semaphoreShared)
        *_semaphoreShared = false;

    std::cout << __func__ << std::endl;
} // ... and waiting for future destruction

void RandomDataSource::run(const std::shared_ptr<DataReceiver> receiver)
{
    if (_semaphoreShared) {
        *_semaphoreShared = false;
        _futureOptional.reset(); // waiting for future destruction

        *_semaphoreShared = true;
        _futureOptional = std::async(std::launch::async, [receiver, semaphoreShared = _semaphoreShared](){
            while (semaphoreShared && *semaphoreShared && receiver) {
                receiver->dataArrived(rand());
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        });
    }
}
