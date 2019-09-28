#pragma once

#include <string>
#include <memory>

class Listener
{
public:
    virtual ~Listener() = default;

    virtual void processData(const std::shared_ptr<const std::string> data) = 0;
};
