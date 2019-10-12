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
        auto simpleZomby = SimpleZomby::Zomby::create();
        simpleZomby->initWithListener(writeToConsoleListener);
        simpleZomby->run();

        auto steppingZomby = SteppingZomby::Zomby::create();
        steppingZomby->initWithListener(writeToConsoleListener);
        steppingZomby->run();

        auto complicatedZomby = ComplicatedZomby::Zomby::create();
        complicatedZomby->initWithListener(writeToConsoleListener);
        complicatedZomby->run();

        auto boozdedZomby = BoozdedZomby::Zomby::create();
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
