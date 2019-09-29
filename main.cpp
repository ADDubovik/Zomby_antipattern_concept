#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <sstream>

#include "SimpleZomby/SimpleZomby.h"
#include "ComplicatedZomby/Impl/ComplicatedZomby.h"
#include "BoozdedZomby/Impl/BoozdedZomby.h"
#include "Common/Impl/WriteToConsoleListener.h"

int main()
{
    auto writeToConsoleListener = std::make_shared<Common::WriteToConsoleListener>();

    {
        auto simpleZomby = std::make_shared<SimpleZomby>();
        simpleZomby->run(writeToConsoleListener);

        auto complicatedZomby = std::make_shared<ComplicatedZomby::Zomby>();
        complicatedZomby->run(writeToConsoleListener);

        auto boozdedZomby = std::make_shared<BoozdedZomby::Zomby>();
        boozdedZomby->run(writeToConsoleListener);

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
