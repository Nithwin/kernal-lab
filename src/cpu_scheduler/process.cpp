#include "cpu_scheduler/process.h"

Process::Process(
    int pid, int arrivalTime, int burstTime, int priority
) : pid(pid),
    arrivalTime(arrivalTime),
    burstTime(burstTime),
    priority(priority),
    ProcessState(ProcessState::New),
    remainingTime(burstTime),
    startTime(-1),
    completionTime(-1),
    {
        
    }