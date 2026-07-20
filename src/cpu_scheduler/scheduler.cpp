#include "cpu_scheduler/scheduler.h"

void Scheduler::startProcess(Process &process, int currentTime)
{
    if (process.getStartTime() == -1)
    {
        process.setStartTime(currentTime);
    }
    process.setState(ProcessState::Running);
}

void Scheduler::finishProcess(Process &process, int currentTime)
{
    process.setCompletionTime(currentTime);
    process.setRemainingTime(0);
    process.setState(ProcessState::Terminated);

    int turnaround =
        process.getCompletionTime() -
        process.getArrivalTime();

    process.setTurnaroundTime(turnaround);

    int waiting =
        turnaround -
        process.getBurstTime();

    process.setWaitingTime(waiting);

    int response =
        process.getStartTime() -
        process.getArrivalTime();

    process.setResponseTime(response);
}