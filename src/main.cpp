#include <iostream>
#include <vector>
#include "cpu_scheduler/process.h"
#include "cpu_scheduler/algorithms/fcfs.h"

int main(){
    std::vector<Process> processes = {
        Process(1, 0, 5, 1),
        Process(2, 2, 3, 1),
        Process(3, 4, 1, 1)
    };

    FCFSScheduler scheduler;
    scheduler.schedule(processes);
    return 0;
}