#include <iostream>
#include "cpu_scheduler/process.h"
#include "cpu_scheduler/algorithms/fcfs.h"
#include "cpu_scheduler/utils/schedule_printer.h"
#include <vector>

/**
 * @brief Test for the CPU Scheduling Module.
 * 
 * Demonstrates how to use CPU Scheduling algorithms like FCFS.
 */
int main() {
    std::cout << "--- CPU Scheduling Module Test ---\n";
    std::vector<Process> processes = {
        Process(1, 0, 5, 1, 900),
        Process(2, 1, 4, 2, 500)
    };

    FCFSScheduler fcfsScheduler;
    fcfsScheduler.schedule(processes);
    
    std::cout << "Processes scheduled with FCFS.\n";
    for(const auto& p : processes) {
        std::cout << "PID: " << p.getPid() << " | Turnaround Time: " << p.getTurnaroundTime() << "\n";
    }

    return 0;
}
