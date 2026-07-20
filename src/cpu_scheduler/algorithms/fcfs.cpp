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

        startProcess(process, currentTime);

        currentTime += process.getBurstTime();

        finishProcess(process, currentTime);
    }
}