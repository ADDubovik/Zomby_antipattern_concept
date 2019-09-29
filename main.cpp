#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "ComplicatedZomby/Impl/ComplicatedZomby.h"
#include "SimpleZomby/SimpleZomby.h"
#include "WriteToConsoleListener.h"

int main()
{
    {
        auto simpleZomby = std::make_shared<SimpleZomby>();
        simpleZomby->runSomethingAsync();

        auto complicatedZomby = std::make_shared<ComplicatedZomby>();
        auto writeToConsoleListener = std::make_shared<WriteToConsoleListener>();
        complicatedZomby->run(writeToConsoleListener);

        std::this_thread::sleep_for(std::chrono::milliseconds(4500));
    } // Zombies should be killed here

    std::cout << "Zombies were killed" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}
