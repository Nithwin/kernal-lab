/**
 * @file scheduler.cpp
 * @brief Base Scheduler class implementation providing timing calculation helpers.
 *
 * CONCEPT:
 *   The Scheduler base class defines common life-cycle hooks for processes:
 *   - startProcess(): Called when a process gets the CPU for the first time.
 *   - finishProcess(): Called when a process completes, automatically computing:
 *       1. Turnaround Time = Completion Time - Arrival Time
 *       2. Waiting Time = Turnaround Time - Burst Time
 *       3. Response Time = Start Time - Arrival Time
 */

#include "cpu_scheduler/scheduler.h"

/**
 * @brief Marks the start of process execution and updates its state to Running.
 *
 * @param process Reference to the process being started.
 * @param currentTime Current simulation clock time.
 */
void Scheduler::startProcess(Process &process, int currentTime)
{
    // Record start time only on first execution (important for preemptive algorithms)
    if (process.getStartTime() == -1)
    {
        process.setStartTime(currentTime);
    }
    process.setState(ProcessState::Running);
}

/**
 * @brief Marks process completion and calculates all scheduling performance metrics.
 *
 * @param process Reference to the completed process.
 * @param currentTime Current simulation clock time.
 */
void Scheduler::finishProcess(Process &process, int currentTime)
{
    process.setCompletionTime(currentTime);
    process.setRemainingTime(0);
    process.setState(ProcessState::Terminated);

    // Turnaround Time (TAT) = Completion Time - Arrival Time
    int turnaround = process.getCompletionTime() - process.getArrivalTime();
    process.setTurnaroundTime(turnaround);

    // Waiting Time (WT) = Turnaround Time - Burst Time
    int waiting = turnaround - process.getBurstTime();
    process.setWaitingTime(waiting);

    // Response Time (RT) = Start Time - Arrival Time
    int response = process.getStartTime() - process.getArrivalTime();
    process.setResponseTime(response);
}