#include <iostream>
#include <thread>
#include <chrono>

#include "estop.hpp"

class TestEstop : public Estop
{
public:
    TestEstop() : Estop() {}

protected:
    void estop(int sig) override
    {
        std::cout << "Emergency stop triggered." << std::endl;
    }
};

int main(void)
{
    TestEstop test_estop;
    std::cout << "Press Ctrl+C to test emergency stop." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    return EXIT_SUCCESS;
}