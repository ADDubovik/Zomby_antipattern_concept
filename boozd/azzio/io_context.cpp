#include <iostream>

#include "io_context.h"
#include "stream.h"

namespace boozd::azzio {
io_context::~io_context()
{
    std::cout << typeid(*this).name() << "::" << __func__ << std::endl;
}

void io_context::async_read(buffer& buf, stream& s, io_context::handler&& h)
{
    _pack_shared = std::make_shared<pack>(buf, s);
	_handler_shared = std::make_shared<handler>(std::move(h));
}

void io_context::run()
{
    if (_pack_shared && _handler_shared) {
		auto& [buf, s] = *_pack_shared;
		using namespace std::chrono;
        auto start = steady_clock::now();
		while (duration_cast<milliseconds>(steady_clock::now() - start).count() < 1000) {
            if (auto read = s.read())
                buf.emplace_back(*read);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        (*_handler_shared)(error_code::no_error);
	}
}
} // namespace boozd::azzio
