#pragma once

#include <functional>
#include <vector>
#include <atomic>
#include <optional>
#include <future>

namespace boozd::azzio {
class io_context
{
public:
    io_context();
    ~io_context();

    io_context(const io_context&) = delete;
    io_context(io_context&&) = delete;
    io_context& operator=(const io_context&) = delete;
    io_context& operator=(io_context&&) = delete;

    enum class error_code {no_error, good_error, bad_error, unknown_error, known_error, well_known_error};
    using buffer = std::vector<int>;
    using stream = std::function<int()>;
    using handler = std::function<void(error_code)>;

    // Start an asynchronous operation to read a certain amount of data from a stream.
    // This function is used to asynchronously read a certain number of bytes of data from a stream.
    // The function call always returns immediately.
    void async_read(buffer& buf, stream& s, handler&& h);

    // Run the io_context object's event processing loop.
    void run();
private:
    using pack = std::tuple<buffer&, stream&, handler&&>;
    using pack_shared = std::shared_ptr<pack>;
    using semaphore = std::atomic<bool>;
    using semaphore_shared = std::shared_ptr<semaphore>;

    pack_shared _pack_shared;
    const semaphore_shared _semaphore_shared = std::make_shared<semaphore>(false);
    std::optional<std::future<void>> _future_optional;
};
} // namespace boozd::azzio
