#include <chrono>
#include <thread>
#include <sstream>

#include "Common/Impl/WriteToConsoleListener.h"
#include "Common/Impl/ThreadJoinerAsync.h"
#include "SimpleZomby/SimpleZomby.h"

int main()
{
    auto writeToConsoleListener = Common::WriteToConsoleListener::instance();
    auto joiner = std::make_shared<Common::ThreadJoinerAsync>();

    {
        auto simpleZomby = SimpleZomby::Zomby(joiner);
        simpleZomby.runOnce(writeToConsoleListener);

        std::this_thread::sleep_for(std::chrono::milliseconds(4500));
    } // Zomby should be killed here

    {
        std::ostringstream buf;
        buf << "============================================================\n"
            << "|                      Zomby was killed                    |\n"
            << "============================================================\n";
        if (writeToConsoleListener) {
            writeToConsoleListener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}
