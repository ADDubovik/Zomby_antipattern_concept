#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "Common/Impl/ThreadJoinerAsync.h"

class DurationPrinter
{
public:
    DurationPrinter(const std::string& prefix)
        : _start(std::chrono::steady_clock::now())
        , _prefix(prefix)
    {
    }

    ~DurationPrinter()
    {
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start);
        std::cout << _prefix << duration.count() << " milliseconds" << std::endl;
    }

    DurationPrinter(const DurationPrinter&) = delete;
    DurationPrinter(const DurationPrinter&&) = delete;
    DurationPrinter& operator=(const DurationPrinter&) = delete;
    DurationPrinter& operator=(DurationPrinter&&) = delete;

private:
    std::chrono::steady_clock::time_point _start;
    std::string _prefix;
};

int main()
{
    {
        auto durationPrinter = DurationPrinter("Test 1: ");
        {
            auto joiner = Common::ThreadJoinerAsync();
        }
    }

    {
        auto durationPrinter = DurationPrinter("Test 2: ");
        {
            auto joiner = Common::ThreadJoinerAsync();
            auto thread = std::thread([](){});
            joiner.join(std::move(thread));
        }
    }

    {
        auto durationPrinter3a = DurationPrinter("Test 3a: ");
        {
            auto joiner = Common::ThreadJoinerAsync();
            auto thread = std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300)); });
            {
                auto durationPrinter3b = DurationPrinter("Test 3b: ");
                joiner.join(std::move(thread));
            }
        }
    }

    {
        auto durationPrinter4a = DurationPrinter("Test 4a: ");
        {
            const size_t count = 100;
            auto joiner = Common::ThreadJoinerAsync();
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300)); }));
            }

            {
                auto durationPrinter4b = DurationPrinter("Test 4b: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                }
            }
        }
    }

    {
        const size_t count = 100;
        auto joiner = Common::ThreadJoinerAsync();
        auto threads = std::vector<std::thread>();
        threads.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300)); }));
        }

        {
            auto durationPrinter5a = DurationPrinter("Test 5a: ");
            for (auto&& elem : threads) {
                joiner.join(std::move(elem));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        auto durationPrinter5a = DurationPrinter("Test 5b: ");
    }

    {
        const size_t count = 100;
        auto durationPrinter6a = DurationPrinter("Test 6a: ");
        auto joiner = Common::ThreadJoinerAsync();
        {
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300)); }));
            }

            {
                auto durationPrinter6b = DurationPrinter("Test 6b: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        {
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300)); }));
            }

            {
                auto durationPrinter6c = DurationPrinter("Test 6c: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                }
            }
        }
    }

    {
        const size_t count = 100;
        auto durationPrinter7a = DurationPrinter("Test 7a: ");
        auto joiner = Common::ThreadJoinerAsync();
        {
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300)); }));
            }

            {
                auto durationPrinter7b = DurationPrinter("Test 7b: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        {
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300)); }));
            }

            {
                auto durationPrinter7c = DurationPrinter("Test 7c: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                }
            }
        }
    }

    {
        const size_t count = 100;
        auto durationPrinter8a = DurationPrinter("Test 8a: ");
        auto joiner = Common::ThreadJoinerAsync();
        {
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([i](){ std::this_thread::sleep_for(std::chrono::milliseconds(300 + 5 * i)); }));
            }

            {
                auto durationPrinter8b = DurationPrinter("Test 8b: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                }
            }
        }
    }

    {
        const size_t count = 100;
        auto durationPrinter9a = DurationPrinter("Test 9a: ");
        auto joiner = Common::ThreadJoinerAsync();
        {
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300 + 20 * (rand() & 0xf))); }));
            }

            {
                auto durationPrinter9b = DurationPrinter("Test 9b: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                }
            }
        }
    }

    {
        const size_t count = 100;
        auto durationPrinter10a = DurationPrinter("Test 10a: ");
        auto joiner = Common::ThreadJoinerAsync();
        {
            auto threads = std::vector<std::thread>();
            threads.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                threads.emplace_back(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(300 + 20 * (rand() & 0xf))); }));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            {
                auto durationPrinter10b = DurationPrinter("Test 10b: ");
                for (auto&& elem : threads) {
                    joiner.join(std::move(elem));
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        }
    }

    {
        const size_t count = 100;
        auto durationPrinter11 = DurationPrinter("Test 11: ");
        auto joiner = Common::ThreadJoinerAsync();
        {
            for (size_t i = 0; i < count; ++i) {
                joiner.join(std::thread([](){ std::this_thread::sleep_for(std::chrono::milliseconds(10)); }));
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }
}
