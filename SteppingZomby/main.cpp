#include <chrono>
#include <thread>
#include <sstream>

#include "SteppingZomby/SteppingZomby.h"
#include "Common/Impl/WriteToConsoleListener.h"

int main()
{
    auto writeToConsoleListener = Common::WriteToConsoleListener::instance();

    {
        auto steppingZomby = SteppingZomby::Zomby::create();
        steppingZomby->initWithListener(writeToConsoleListener);
        steppingZomby->run();

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    } // Zombies should be killed here

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
