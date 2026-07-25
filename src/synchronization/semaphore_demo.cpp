#include <chrono>
#include <iostream>
#include <random>
#include <semaphore>
#include <thread>
#include <vector>

using namespace std;

std::counting_semaphore<3> parkingLot(3);

void parkCar(int id)
{
    cout << "Car " << id << " arrived.\n";

    parkingLot.acquire();

    cout << "Car " << id << " entered the parking lot.\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, 5);

    this_thread::sleep_for(chrono::seconds(dist(gen)));

    cout << "Car " << id << " left the parking lot.\n";

    parkingLot.release();
}

int main()
{
    vector<thread> cars;

    for (int i = 1; i <= 8; i++)
    {
        cars.emplace_back(parkCar, i);

        this_thread::sleep_for(chrono::milliseconds(300));
    }

    for (auto &car : cars)
    {
        car.join();
    }

    return 0;
}