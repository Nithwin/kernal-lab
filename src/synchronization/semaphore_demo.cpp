/**
 * @file semaphore_demo.cpp
 * @brief Demonstrates Counting Semaphores using a parking lot analogy.
 *
 * THE CONCEPT:
 *   A counting semaphore maintains an internal counter that represents
 *   the number of available resources. Unlike a mutex (which is binary),
 *   a semaphore can allow UP TO N threads to access a resource simultaneously.
 *
 *   - acquire() → Decrements the counter. If counter reaches 0, the thread BLOCKS.
 *   - release() → Increments the counter. Wakes up a blocked thread.
 *
 * THE ANALOGY:
 *   A parking lot with 3 spaces. Cars (threads) arrive and try to park:
 *   - If a space is available → park immediately.
 *   - If the lot is full → wait until a car leaves.
 *
 * IN THIS DEMO:
 *   We create 8 cars (threads) trying to use a parking lot with 3 spaces.
 *   Only 3 cars can be parked at any time. The others wait their turn.
 *
 * BUILD & RUN:
 *   cmake -B build -S . && cmake --build build && ./build/test_sync_semaphore
 */

#include <chrono>
#include <iostream>
#include <random>
#include <semaphore>
#include <thread>
#include <vector>

using namespace std;

// A counting semaphore initialized with 3 — represents 3 parking spaces.
// Template parameter <3> is the maximum value the semaphore can reach.
std::counting_semaphore<3> parkingLot(3);

/**
 * @brief Simulates a car arriving, parking, and leaving.
 *
 * @param id The car's ID number.
 *
 * Steps:
 *   1. Car arrives (prints message).
 *   2. acquire() — Tries to get a parking space.
 *      If all 3 are taken → BLOCKS until one is released.
 *   3. Car parks for a random duration (2-5 seconds).
 *   4. release() — Frees the parking space for another car.
 */
void parkCar(int id)
{
    cout << "Car " << id << " arrived.\n";

    // acquire(): Decrements the internal counter.
    // If counter > 0 → proceed (got a space).
    // If counter == 0 → BLOCK until someone calls release().
    parkingLot.acquire();

    cout << "Car " << id << " entered the parking lot.\n";

    // Simulate parking for a random 2-5 seconds.
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, 5);

    this_thread::sleep_for(chrono::seconds(dist(gen)));

    cout << "Car " << id << " left the parking lot.\n";

    // release(): Increments the internal counter.
    // If any thread is blocked on acquire(), one is woken up.
    parkingLot.release();
}

int main()
{
    vector<thread> cars;

    // Create 8 cars (threads). Only 3 can park at a time!
    for (int i = 1; i <= 8; i++)
    {
        cars.emplace_back(parkCar, i);

        // Small delay between car arrivals for realistic output.
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    // Wait for all cars to finish.
    for (auto &car : cars)
    {
        car.join();
    }

    return 0;
}