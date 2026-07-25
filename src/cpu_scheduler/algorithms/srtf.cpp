/**
 * @file srtf.cpp
 * @brief Shortest Remaining Time First (SRTF) Preemptive CPU Scheduling Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Preemptive version of Shortest Job First (SJF).
 *   - At every time tick (1 unit), the scheduler checks if a newly arrived process
 *     has a shorter remaining execution time than the current running process.
 *   - If yes, the current process is preempted and put back into the ready state.
 *
 * PROS:
 *   - Gives optimal average waiting time for preemptive systems.
 *   - Excellent response time for short interactive processes.
 *
 * CONS:
 *   - High context-switch overhead due to frequent preemption.
 *   - Potential starvation for long-running processes.
 */

#include "cpu_scheduler/algorithms/srtf.h"

void SRTFScheduler::schedule(std::vector<Process> &processes)
{
    if (processes.empty()) return;

    int currentTime = 0;
    size_t completedProcesses = 0;

    // Simulation runs unit-by-unit (tick-by-tick)
    while (completedProcesses < processes.size())
    {
        Process *selectedProcess = nullptr;

        // Step 1: Find the ready process with the shortest remaining time
        for (Process &process : processes)
        {
            if (process.getState() == ProcessState::Terminated) continue;
            if (process.getArrivalTime() > currentTime) continue;

            if (selectedProcess == nullptr)
            {
                selectedProcess = &process;
            }
            else if (process.getRemainingTime() < selectedProcess->getRemainingTime())
            {
                selectedProcess = &process;
            }
            else if (process.getRemainingTime() == selectedProcess->getRemainingTime())
            {
                // Tie-breaker: earlier arrival time, then lower PID
                if (process.getArrivalTime() < selectedProcess->getArrivalTime())
                {
                    selectedProcess = &process;
                }
                else if (process.getArrivalTime() == selectedProcess->getArrivalTime())
                {
                    if (process.getPid() < selectedProcess->getPid())
                    {
                        selectedProcess = &process;
                    }
                }
            }
        }

        // CPU is idle if no process has arrived
        if (selectedProcess == nullptr)
        {
            currentTime++;
            continue;
        }

        // Step 2: Start/Resume execution of the selected process
        startProcess(*selectedProcess, currentTime);

        // Step 3: Run for 1 time unit (preemptive tick)
        selectedProcess->setRemainingTime(selectedProcess->getRemainingTime() - 1);
        currentTime++;

        // Step 4: Check if process finished or needs preemption
        if (selectedProcess->getRemainingTime() == 0)
        {
            finishProcess(*selectedProcess, currentTime);
            completedProcesses++;
        }
        else
        {
            // Preempt: Return state to Ready so another process can run next tick
            selectedProcess->setState(ProcessState::Ready);
        }
    }
}