/**
 * @file fcfs.cpp
 * @brief First-Come, First-Served (FCFS) CPU Scheduling Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Non-preemptive scheduling policy.
 *   - Processes are dispatched in the exact order of their arrival.
 *   - If two processes arrive at the same time, PID is used as tie-breaker.
 *
 * PROS:
 *   - Simple to implement using FIFO queue.
 *   - No starvation.
 *
 * CONS:
 *   - Convoy Effect: Short processes wait behind long CPU-bound processes.
 *   - High average waiting time.
 */

#include "cpu_scheduler/algorithms/fcfs.h"
#include <algorithm>

void FCFSScheduler::schedule(std::vector<Process> &processes)
{
    if (processes.empty()) return;

    // Step 1: Sort processes by arrival time (earliest first), using PID as tie-breaker
    std::sort(processes.begin(), processes.end(), 
    [](const Process& a, const Process& b)
    {
        if (a.getArrivalTime() == b.getArrivalTime())
        {
            return a.getPid() < b.getPid();
        }
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;

    // Step 2: Sequentially service each process to completion
    for (Process &process : processes) 
    {
        // If CPU is idle, advance simulation clock to process arrival time
        if (currentTime < process.getArrivalTime())
        {
            currentTime = process.getArrivalTime();
        }

        // Record start time and set state to Running
        startProcess(process, currentTime);

        // Run until completion (non-preemptive)
        currentTime += process.getBurstTime();

        // Calculate TAT, WT, RT metrics and set state to Terminated
        finishProcess(process, currentTime);
    }
}