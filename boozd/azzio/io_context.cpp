#include <iostream>
#include <thread>
#include <chrono>

#include "io_context.h"
#include "stream.h"

namespace boozd::azzio {
io_context::~io_context()
{
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void io_context::async_read(stream& s, buffer& buf, io_context::handler&& h)
{
    _pack_optional.emplace(buf, s);
    _handler_optional.emplace(std::move(h));
}

void io_context::run()
{
    if (_pack_optional && _handler_optional) {
        auto& [buf, s] = *_pack_optional;
		using namespace std::chrono;
        auto start = steady_clock::now();
		while (duration_cast<milliseconds>(steady_clock::now() - start).count() < 1000) {
            if (auto read = s.read())
                buf.emplace_back(*read);
            std::this_thread::sleep_for(milliseconds(100));
        }

        (*_handler_optional)(error_code::no_error);
	}
}
} // namespace boozd::azzio
