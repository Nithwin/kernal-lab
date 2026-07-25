/**
 * @file producer_consumer.cpp
 * @brief Demonstrates the classic Producer-Consumer synchronization problem.
 *
 * THE PROBLEM:
 *   Two types of threads share a bounded buffer (queue):
 *   - Producer: Creates items and pushes them into the buffer.
 *   - Consumer: Pops items from the buffer and processes them.
 *
 *   Rules:
 *   - Producer must WAIT if the buffer is full.
 *   - Consumer must WAIT if the buffer is empty.
 *   - Only one thread can access the buffer at a time.
 *
 * THE SOLUTION:
 *   - std::mutex protects the shared buffer (mutual exclusion).
 *   - std::condition_variable lets the consumer sleep until there IS data,
 *     instead of busy-waiting (spinning in a loop checking if buffer is empty).
 *
 * KEY CONCEPTS:
 *   - cv.wait(lock, predicate):
 *       1. Atomically releases the mutex and puts the thread to sleep.
 *       2. Wakes up when notify_one() is called.
 *       3. Re-checks the predicate. If true, proceeds. If false, sleeps again.
 *       (This prevents "spurious wakeups" — a real OS phenomenon!)
 *
 *   - cv.notify_one(): Wakes up ONE waiting thread.
 *
 * BUILD & RUN:
 *   cmake -B build -S . && cmake --build build && ./build/test_sync_producer
 */

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// Shared bounded buffer — both producer and consumer access this.
std::queue<int> buffer;

// Mutex to protect the buffer from simultaneous access.
std::mutex mtx;

// Condition variable — lets the consumer sleep until data is available.
std::condition_variable cv;

/**
 * @brief Produces 5 items and pushes them into the shared buffer.
 *
 * After pushing each item, it notifies the consumer that data is available.
 * Sleeps 1 second between items to simulate real work.
 */
void producer()
{
    for (int i = 1; i <= 5; i++)
    {
        {
            // Lock the buffer before modifying it.
            std::lock_guard<std::mutex> lock(mtx);

            buffer.push(i);

            std::cout << "Produced: " << i << std::endl;
        }
        // ^^^ lock_guard is destroyed here, so the mutex is released.

        // Wake up one waiting consumer: "Hey, there's data now!"
        cv.notify_one();

        // Simulate work (producing the next item takes time).
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

/**
 * @brief Consumes 5 items from the shared buffer.
 *
 * Uses a condition variable to sleep until the buffer has items,
 * instead of busy-waiting (which wastes CPU).
 */
void consumer()
{
    for (int i = 1; i <= 5; i++)
    {
        // unique_lock is required by cv.wait() (lock_guard won't work here
        // because cv.wait needs to temporarily release and re-acquire the lock).
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until the buffer is not empty.
        // If buffer is empty → release lock, sleep.
        // When notified → re-acquire lock, check predicate again.
        cv.wait(lock, [] {
            return !buffer.empty();
        });

        // At this point, we hold the lock AND the buffer has data.
        int item = buffer.front();
        buffer.pop();

        std::cout << "Consumed: " << item << std::endl;

        // lock is automatically released here when unique_lock goes out of scope.
    }
}

int main()
{
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    // Wait for both threads to finish.
    producerThread.join();
    consumerThread.join();

    std::cout << "\nAll work completed!" << std::endl;

    return 0;
}