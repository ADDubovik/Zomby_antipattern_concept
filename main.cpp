#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include "ComplexZomby/ComplexZomby.h"
#include "SimpleZomby/SimpleZomby.h"
#include "WriteToConsoleListener.h"

int main()
{
    {
        auto simpleZomby = std::make_shared<SimpleZomby>();
        simpleZomby->runSomethingAsync();

        auto complexZomby = std::make_shared<ComplexZomby>();
        auto writeToConsoleListener = std::make_shared<WriteToConsoleListener>();
        complexZomby->run(writeToConsoleListener);

        std::this_thread::sleep_for(std::chrono::milliseconds(4500));
    } // Zombies should be killed here

    std::cout << "Zombies were killed" << std::endl;

    while (true)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return 0;
}
