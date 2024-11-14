#include <iostream>
#include <chrono>

#include "thread_runner.hpp"

class TestThreadRunner : public ThreadRunner
{
public:
    TestThreadRunner(const int index)
        : ThreadRunner(), _index(index)
    {
        start();
    }

private:
    int _index;

    void run() override
    {
        while (!isStopping())
        {
            std::cout << "ThreadRunner " << _index << " is running." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main(void)
{
    TestThreadRunner test_thread_runner1(1);
    std::cout << "ThreadRunner 1 is starting." << std::endl;
    TestThreadRunner test_thread_runner2(2);
    std::cout << "ThreadRunner 2 is starting." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(10));

    test_thread_runner1.stop();
    std::cout << "ThreadRunner 1 is stopping." << std::endl;
    test_thread_runner2.stop();
    std::cout << "ThreadRunner 2 is stopping." << std::endl;

    test_thread_runner1.wait();
    std::cout << "ThreadRunner 1 is stopped." << std::endl;
    test_thread_runner2.wait();
    std::cout << "ThreadRunner 2 is stopped." << std::endl;

    return EXIT_SUCCESS;
}