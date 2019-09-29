#include <iostream>

#include "azzio.h"

namespace boozd::azzio {
io_context::io_context()
    : _semaphore_shared(std::make_shared<semaphore>(false))
{
}

io_context::~io_context()
{
    if (_semaphore_shared)
        *_semaphore_shared = false;

    std::cout << __func__ << std::endl;
}

void io_context::async_read(io_context::buffer& buf, io_context::stream& s, io_context::handler&& h)
{
    _pack_shared = std::make_shared<pack>(buf, s, std::move(h));
}

void io_context::run()
{
    if (_pack_shared && _semaphore_shared) {
        *_semaphore_shared = false;
        _future_optional.reset(); // waiting for future destruction

        *_semaphore_shared = true;
        _future_optional = std::async(std::launch::async, [pack_shared = _pack_shared, semaphore_shared = _semaphore_shared]() {
            if (pack_shared) {
                auto& [buf, s, h] = *pack_shared;
                using namespace std::chrono;
                auto start = steady_clock::now();
                while (semaphore_shared && *semaphore_shared && (duration_cast<milliseconds>(steady_clock::now() - start).count() < 1000)) {
                    if (!(rand() & 0xff))
                        buf.emplace_back(s());
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }

                h(error_code::no_error);
            }
        });
    }
}
} // namespace boozd::azzio
