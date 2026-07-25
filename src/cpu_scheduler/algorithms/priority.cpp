/**
 * @file priority.cpp
 * @brief Priority-Based Non-Preemptive CPU Scheduling Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Each process is assigned a priority integer.
 *   - Lower numerical value represents HIGHER priority (e.g., Priority 1 > Priority 2).
 *   - The scheduler selects the available process with the highest priority.
 *
 * TIE-BREAKING RULE:
 *   Higher Priority -> Earlier Arrival Time -> Lower PID.
 *
 * STARVATION & AGING:
 *   - High-priority processes can starve low-priority processes indefinitely.
 *   - "Aging" is a technique used in real OSs to gradually increase waiting process priorities.
 */

#include "cpu_scheduler/algorithms/priority.h"
#include <algorithm>

void PriorityScheduler::schedule(std::vector<Process> &processes)
{
    if (processes.empty()) return;

    int currentTime = 0;
    size_t completedProcesses = 0;

    while (completedProcesses < processes.size())
    {
        Process *selectedProcess = nullptr;

        // Find arrived process with the highest priority (smallest priority number)
        for (Process &process : processes)
        {
            if (process.getState() == ProcessState::Terminated) continue;
            if (process.getArrivalTime() > currentTime) continue;

            if (selectedProcess == nullptr)
            {
                selectedProcess = &process;
            }
            else if (process.getPriority() < selectedProcess->getPriority())
            {
                selectedProcess = &process;
            }
            else if (process.getPriority() == selectedProcess->getPriority())
            {
                // Tie-breaker: earlier arrival, then lower PID
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

        // CPU is idle if no process arrived yet
        if (selectedProcess == nullptr)
        {
            currentTime++;
            continue;
        }

        // Run selected high-priority process to completion
        startProcess(*selectedProcess, currentTime);
        currentTime += selectedProcess->getBurstTime();
        finishProcess(*selectedProcess, currentTime);

        completedProcesses++;
    }
}