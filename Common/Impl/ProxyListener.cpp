#include "ProxyListener.h"

namespace Common {
Common::ProxyListener::ProxyListener(std::shared_ptr<Common::Listener> listener)
    : _listener(listener)
{
}

ProxyListener::~ProxyListener() = default;

void ProxyListener::processData(const std::shared_ptr<const Listener::Data> data)
{
    if (auto listener = _listener) {
        listener->processData(data);
    }
}

void ProxyListener::disconnect()
{
    _listener.reset();
}
} // namespace Common
