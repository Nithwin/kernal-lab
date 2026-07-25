/**
 * @file sjf.cpp
 * @brief Shortest Job First (SJF) Non-Preemptive CPU Scheduling Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Non-preemptive algorithm that selects the arrived process with the smallest Burst Time.
 *   - Mathematically proven to minimize average waiting time for a set of processes.
 *
 * SELECTION CRITERIA:
 *   1. Must have arrived (ArrivalTime <= CurrentTime).
 *   2. Must not be terminated.
 *   3. Smallest BurstTime wins.
 *   4. Tie-breakers: Earlier Arrival Time -> Lower PID.
 *
 * CONS:
 *   - Impossible to know exact burst time in advance in real systems.
 *   - Can cause Starvation for long processes if short processes keep arriving.
 */

#include "cpu_scheduler/algorithms/sjf.h"
#include <algorithm>

void SJFScheduler::schedule(std::vector<Process>& processes)
{
    if (processes.empty()) return;

    int currentTime = 0;
    size_t completedProcesses = 0;

    // Loop until all processes finish
    while (completedProcesses < processes.size())
    {
        Process *selectedProcess = nullptr;

        // Scan all arrived processes to find the one with shortest burst time
        for (Process& process : processes) 
        {
            if (process.getState() == ProcessState::Terminated) continue;
            if (process.getArrivalTime() > currentTime) continue; // Not arrived yet

            if (selectedProcess == nullptr)
            {
                selectedProcess = &process;
            }
            else if (process.getBurstTime() < selectedProcess->getBurstTime()) 
            {   
                // Found a process with strictly shorter burst time
                selectedProcess = &process;
            }
            else if (process.getBurstTime() == selectedProcess->getBurstTime())
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

        // If no arrived process found, CPU is idle; advance time by 1 unit
        if (selectedProcess == nullptr)
        {
            currentTime++;
            continue;
        }

        // Execute the selected process to completion (non-preemptive)
        startProcess(*selectedProcess, currentTime);
        currentTime += selectedProcess->getBurstTime();
        finishProcess(*selectedProcess, currentTime);

        completedProcesses++;
    }
}