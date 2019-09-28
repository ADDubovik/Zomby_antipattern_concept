#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <future>

class Zomby : public std::enable_shared_from_this<Zomby>
{
public:
    void runSomethingAsync();

private:
    std::future<void> _future;
};

void Zomby::runSomethingAsync()
{
    _future = std::async(std::launch::async, [shis = shared_from_this()](){
        while(true) {
            std::cout << "Zomby is alive!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });
}

int main()
{
    {
        auto zomby = std::make_shared<Zomby>();
        zomby->runSomethingAsync();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    } // Zomby should be killed here

    std::cout << "Zomby was killed" << std::endl;

    while (true)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    return 0;
}
