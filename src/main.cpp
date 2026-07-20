#include <iostream>
#include <vector>
#include <iomanip>
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

    std::cout << "| PID | Arrival | Burst | Start | Completion | Waiting | Turnaround | Response |\n";
    std::cout << "| --: | ------: | ----: | ----: | ---------: | ------: | ---------: | -------: |\n";
    for(const auto& process: processes)
    {
        std::cout << "| " << std::setw(3) << process.getPid()
                  << " | " << std::setw(7) << process.getArrivalTime()
                  << " | " << std::setw(5) << process.getBurstTime()
                  << " | " << std::setw(5) << process.getStartTime()
                  << " | " << std::setw(10) << process.getCompletionTime()
                  << " | " << std::setw(7) << process.getWaitingTime()
                  << " | " << std::setw(10) << process.getTurnaroundTime()
                  << " | " << std::setw(8) << process.getResponseTime()
                  << " |\n";
    }
    std::cout << "\n\n";
    return 0;
}