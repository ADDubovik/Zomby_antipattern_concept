#pragma once

#include "ComplexZomby/Listener.h"

class WriteToConsoleListener final : public Listener
{
public:
    ~WriteToConsoleListener() override;

    void processData(const std::shared_ptr<const std::string> data) override;
};
