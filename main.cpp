#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <sstream>

#include "SimpleZomby/SimpleZomby.h"
#include "SteppingZomby/SteppingZomby.h"
#include "ComplicatedZomby/Impl/ComplicatedZomby.h"
#include "BoozdedZomby/Impl/BoozdedZomby.h"
#include "Common/Impl/WriteToConsoleListener.h"

int main()
{
    auto writeToConsoleListener = std::make_shared<Common::WriteToConsoleListener>();

    {
        auto simpleZomby = std::make_shared<SimpleZomby::Zomby>();
        simpleZomby->initWithListener(writeToConsoleListener);
        simpleZomby->run();

        auto steppingZomby = std::make_shared<SteppingZomby::Zomby>();
        steppingZomby->initWithListener(writeToConsoleListener);
        steppingZomby->run();

        auto complicatedZomby = std::make_shared<ComplicatedZomby::Zomby>();
        complicatedZomby->initWithListener(writeToConsoleListener);
        complicatedZomby->run();

        auto boozdedZomby = std::make_shared<BoozdedZomby::Zomby>();
        boozdedZomby->initWithListener(writeToConsoleListener);
        boozdedZomby->run();

        std::this_thread::sleep_for(std::chrono::milliseconds(4500));
    } // Zombies should be killed here

    {
        std::ostringstream buf;
        buf << "============================================================\n"
            << "|                    Zombies were killed                   |\n"
            << "============================================================\n";
        if (writeToConsoleListener)
            writeToConsoleListener->processData(std::make_shared<Common::Listener::Data>(buf.str()));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}
