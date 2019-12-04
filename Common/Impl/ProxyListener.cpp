#include "ProxyListener.h"

namespace Common {
Common::ProxyListener::ProxyListener(std::shared_ptr<Common::Listener> listener)
    : _listener(listener)
{
}

ProxyListener::~ProxyListener() = default;

void ProxyListener::processData(const std::shared_ptr<const Listener::Data> data)
{
    auto lockGuard = std::lock_guard(_mutex);
    if (_listener) {
        _listener->processData(data);
    }
}

void ProxyListener::disconnect()
{
    auto lockGuard = std::lock_guard(_mutex);
    _listener.reset();
}
} // namespace Common
