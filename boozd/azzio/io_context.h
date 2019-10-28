#pragma once

#include <functional>
#include <optional>

#include "buffer.h"

namespace boozd::azzio {
class stream;

class io_context
{
public:
    ~io_context();

    enum class error_code {no_error, good_error, bad_error, unknown_error, known_error, well_known_error};
    using handler = std::function<void(error_code)>;

    // Start an asynchronous operation to read a certain amount of data from a stream.
    // This function is used to asynchronously read a certain number of bytes of data from a stream.
    // The function call always returns immediately.
    void async_read(stream& s, buffer& buf, handler&& h);

    // Run the io_context object's event processing loop.
    void run();

private:
    using pack = std::tuple<buffer&, stream&>;
    using pack_optional = std::optional<pack>;
    using handler_optional = std::optional<handler>;

    pack_optional _pack_optional;
    handler_optional _handler_optional;
};
} // namespace boozd::azzio
