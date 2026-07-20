#include "cpu_scheduler/algorithms/fcfs.h"
#include <algorithm>

void FCFSScheduler::schedule(std::vector<Process> &processes)
{
    // if list is empty then return
    if(processes.empty()) return;

    // Sorting the processes to main the order of process which arrived first
    std::sort(processes.begin(), processes.end(), 
    [](const Process& a, const Process& b)
    {
        // if same arrival time then sort by pid
        if (a.getArrivalTime() == b.getArrivalTime())
        {
            return a.getPid() < b.getPid();
        }
        // sort by arrival time
        return a.getArrivalTime() < b.getArrivalTime();
    });

    // to keep track of time
    int currentTime = 0;

    // iterate through all the processes
    for(Process &process: processes) 
    {
        // if current time is less than arrival time, then set current time to arrival time
        // this means the process has to wait for the cpu to be free
        if(currentTime < process.getArrivalTime())
        {
            currentTime = process.getArrivalTime();
        }

        // setting the start time of the process
        process.setStartTime(currentTime);
        process.setState(ProcessState::Running);

        // updating the current time
        currentTime += process.getBurstTime();

        // setting the completion time of the process
        process.setCompletionTime(currentTime);
        process.setState(ProcessState::Terminated);
        process.setRemainingTime(0);

        // calculating turnaround time
        int turnaroundTime = process.getCompletionTime() - process.getArrivalTime();
        process.setTurnaroundTime(turnaroundTime);

        // calculating waiting time
        int waitingTime = turnaroundTime - process.getBurstTime();
        process.setWaitingTime(waitingTime);

        // calculating response time
        int responseTime = process.getStartTime() - process.getArrivalTime();
        process.setResponseTime(responseTime);
    }
}