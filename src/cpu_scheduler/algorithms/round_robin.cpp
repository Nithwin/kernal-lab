#include "cpu_scheduler/algorithms/round_robin.h"

#include <algorithm>
#include <queue>

RoundRobinScheduler::RoundRobinScheduler(int quantum)
    : quantum(quantum)
{
}

void RoundRobinScheduler::schedule(std::vector<Process> &processes)
{
    if (processes.empty())
        return;

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

    std::queue<Process *> readyQueue;

    while (completed < processes.size())
    {
        // If CPU is idle, jump to the next arriving process
        if (readyQueue.empty())
        {
            currentTime = std::max(currentTime,
                                   processes[nextArrivalIndex].getArrivalTime());

            while (nextArrivalIndex < processes.size() &&
                   processes[nextArrivalIndex].getArrivalTime() <= currentTime)
            {
                readyQueue.push(&processes[nextArrivalIndex]);
                nextArrivalIndex++;
            }
        }

        Process *current = readyQueue.front();
        readyQueue.pop();

        // Start (records first execution only)
        startProcess(*current, currentTime);

        int executionTime =
            std::min(current->getRemainingTime(), quantum);

        current->setRemainingTime(
            current->getRemainingTime() - executionTime);

        currentTime += executionTime;

        // Add any newly arrived processes
        while (nextArrivalIndex < processes.size() &&
               processes[nextArrivalIndex].getArrivalTime() <= currentTime)
        {
            readyQueue.push(&processes[nextArrivalIndex]);
            nextArrivalIndex++;
        }

        // Finished?
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