#pragma once

#include <mutex>

#include "Common/Listener.h"

namespace Common {
class ProxyListener final : public Listener
{
public:
    ProxyListener() = delete;
    ProxyListener(std::shared_ptr<Listener> listener);
    ProxyListener(const ProxyListener&) = delete;
    ProxyListener(ProxyListener&&) = delete;
    ProxyListener& operator=(const ProxyListener&) = delete;
    ProxyListener& operator=(ProxyListener&&) = delete;

    ~ProxyListener() override;

    // blocking
    void processData(const std::shared_ptr<const Data> data) override;

    void disconnect();

private:
    std::shared_ptr<Listener> _listener;
};
} // namespace Common
