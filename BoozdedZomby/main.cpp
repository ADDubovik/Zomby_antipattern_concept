#include <chrono>
#include <thread>
#include <sstream>

#include "BoozdedZomby/BoozdedZomby.h"
#include "Common/Impl/WriteToConsoleListener.h"

int main()
{
    auto writeToConsoleListener = Common::WriteToConsoleListener::instance();

    {
        auto boozdedZomby = BoozdedZomby::Zomby::create();
        boozdedZomby->initWithListener(writeToConsoleListener);
        boozdedZomby->run();

        std::this_thread::sleep_for(std::chrono::milliseconds(4500));
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
