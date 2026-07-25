#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::queue<int> buffer;
std::mutex mtx;
std::condition_variable cv;

void producer()
{
    for (int i = 1; i <= 5; i++)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);

            buffer.push(i);

            std::cout << "Produced: " << i << std::endl;
        }

        // Wake up one waiting consumer
        cv.notify_one();

        // Simulate work
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumer()
{
    for (int i = 1; i <= 5; i++)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until the buffer is not empty
        cv.wait(lock, [] {
            return !buffer.empty();
        });

        int item = buffer.front();
        buffer.pop();

        std::cout << "Consumed: " << item << std::endl;

        // lock is automatically released here
    }
}

int main()
{
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    std::cout << "\nAll work completed!" << std::endl;

    return 0;
}