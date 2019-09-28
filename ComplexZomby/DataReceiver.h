#pragma once

class DataReceiver
{
public:
    virtual ~DataReceiver() = default;

    virtual void dataArrived(int data) = 0;
};
