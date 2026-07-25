#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex forks[5];

void philosopher(int id)
{
    int left = id;
    int right = (id + 1) % 5;

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::scoped_lock lock(forks[left], forks[right]);

        std::cout << "Philosopher " << id << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
    std::thread philosophers[5];

    for (int i = 0; i < 5; i++)
        philosophers[i] = std::thread(philosopher, i);

    for (int i = 0; i < 5; i++)
        philosophers[i].join();

    return 0;
}