#pragma once

#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <csignal>

class ThreadRunner
{
public:
    enum ThreadState
    {
        RUNNING,
        STOPPING,
        STOPPED
    };

    virtual bool start()
    {
        if (isRunning())
            return false;

        state_ = RUNNING;
        std::thread([this]()
                    {
                        this->run();
                        state_ = STOPPED; })
            .detach();
        return true;
    }

    virtual bool stop()
    {
        if (!isRunning())
            return false;

        std::lock_guard<std::mutex> lock(mutex_);
        state_ = STOPPING;
        return true;
    }

    virtual void wait()
    {
        while (!isStopped())
        {
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
    }

    bool isRunning()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return state_ == RUNNING;
    }

    bool isStopping()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return state_ == STOPPING;
    }

    bool isStopped()
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return state_ == STOPPED;
    }

protected:
    virtual void run() = 0;
    std::mutex mutex_;

private:
    ThreadState state_ = STOPPED;
};