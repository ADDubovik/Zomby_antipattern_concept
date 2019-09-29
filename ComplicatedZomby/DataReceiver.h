#pragma once

namespace ComplicatedZomby {
class DataReceiver
{
public:
    virtual ~DataReceiver() = default;

    virtual void dataArrived(int data) = 0;
};
} // namespace ComplicatedZomby
