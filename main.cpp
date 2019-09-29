#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "SimpleZomby/SimpleZomby.h"
#include "ComplicatedZomby/Impl/ComplicatedZomby.h"
#include "BoozdedZomby/Impl/BoozdedZomby.h"
#include "Common/Impl/WriteToConsoleListener.h"

int main()
{
    {
        auto simpleZomby = std::make_shared<SimpleZomby>();
        simpleZomby->runSomethingAsync();

        auto writeToConsoleListener = std::make_shared<Common::WriteToConsoleListener>();

        auto complicatedZomby = std::make_shared<ComplicatedZomby::Zomby>();
        complicatedZomby->run(writeToConsoleListener);

        auto boozdedZomby = std::make_shared<BoozdedZomby::Zomby>();
        boozdedZomby->run(writeToConsoleListener);

        std::this_thread::sleep_for(std::chrono::milliseconds(4500));
    } // Zombies should be killed here

    std::cout << "============================================================" << std::endl
              << "|                    Zombies were killed                   |" << std::endl
              << "============================================================" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}
