#include "cpu_scheduler/algorithms/fcfs.h"
#include <algorithm>

void FCFSScheduler::schedule(std::vector<Process> &processes)
{
    if(processes.empty()) return;
    // Sorting the processes to main the order of process which arrived first
    std::sort(processes.begin(), processes.end(), 
    [](const Process& a, const Process& b)
    {
        return a.getArrivalTime() < b.getArrivalTime();
    });

    int currentTime = 0;

    for(Process &process: processes) 
    {
        if(currentTime < process.getArrivalTime())
        {
            currentTime = process.getArrivalTime();
        }
        
        process.setStartTime(currentTime);
        process.setState(ProcessState::Running);

        currentTime += process.getBurstTime();

        process.setCompletionTime(currentTime);
        process.setState(ProcessState::Terminated);
        process.setRemainingTime(0);

        int turnaroundTime = process.getCompletionTime() - process.getArrivalTime();
        process.setTurnaroundTime(turnaroundTime);

        int waitingTime = turnaroundTime - process.getBurstTime();
        process.setWaitingTime(waitingTime);

        int responseTime = process.getStartTime() - process.getArrivalTime();
        process.setResponseTime(responseTime);
    }
}