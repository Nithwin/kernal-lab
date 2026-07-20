#pragma once

enum class ProcessState
{
    New,
    Ready,
    Running,
    Waiting,
    Terminated
};

class Process {
    private:
        const int pid;
        const int arrivalTime;
        const int burstTime;
        const int priority;
    public:
        Process(int pid, int arrivalTime, int burstTime, int priority);
};