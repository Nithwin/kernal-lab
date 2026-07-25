/**
 * @file round_robin.cpp
 * @brief Round Robin (RR) Preemptive CPU Scheduling Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Designed for time-sharing systems.
 *   - Assigns a fixed time unit called "Time Quantum" to each process in a FIFO Ready Queue.
 *   - Process runs for min(RemainingTime, Quantum).
 *   - If process doesn't finish within quantum, it is preempted and pushed to back of queue.
 *
 * TIME QUANTUM IMPACT:
 *   - Too small -> High context switch overhead.
 *   - Too large -> Degenerates into FCFS scheduling.
 */

#include "cpu_scheduler/algorithms/round_robin.h"
#include <algorithm>
#include <queue>

RoundRobinScheduler::RoundRobinScheduler(int quantum)
    : quantum(quantum)
{
}

void RoundRobinScheduler::schedule(std::vector<Process> &processes)
{
    if (processes.empty()) return;

    // Sort by arrival time initially to enqueue processes in order of arrival
    std::sort(processes.begin(), processes.end(),
              [](const Process &a, const Process &b)
              {
                  if (a.getArrivalTime() == b.getArrivalTime())
                  {
                      return a.getPid() < b.getPid();
                  }
                  return a.getArrivalTime() < b.getArrivalTime();
              });

    int currentTime = 0;
    size_t completed = 0;
    size_t nextArrivalIndex = 0;

    // Ready Queue storing pointers to processes ready for CPU
    std::queue<Process *> readyQueue;

    while (completed < processes.size())
    {
        // If ready queue is empty, jump current time to next arriving process
        if (readyQueue.empty())
        {
            currentTime = std::max(currentTime, processes[nextArrivalIndex].getArrivalTime());

            while (nextArrivalIndex < processes.size() &&
                   processes[nextArrivalIndex].getArrivalTime() <= currentTime)
            {
                readyQueue.push(&processes[nextArrivalIndex]);
                nextArrivalIndex++;
            }
        }

        // Pop process at front of queue
        Process *current = readyQueue.front();
        readyQueue.pop();

        // Start or resume execution
        startProcess(*current, currentTime);

        // Execute for at most one time quantum
        int executionTime = std::min(current->getRemainingTime(), quantum);
        current->setRemainingTime(current->getRemainingTime() - executionTime);
        currentTime += executionTime;

        // Enqueue any new processes that arrived during this quantum execution
        while (nextArrivalIndex < processes.size() &&
               processes[nextArrivalIndex].getArrivalTime() <= currentTime)
        {
            readyQueue.push(&processes[nextArrivalIndex]);
            nextArrivalIndex++;
        }

        // If process finished, mark terminated; otherwise re-queue it
        if (current->getRemainingTime() == 0)
        {
            finishProcess(*current, currentTime);
            completed++;
        }
        else
        {
            current->setState(ProcessState::Ready);
            readyQueue.push(current);
        }
    }
}