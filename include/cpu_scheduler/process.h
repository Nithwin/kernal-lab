#pragma once

// Process State - Represents the state of a process
enum class ProcessState
{
    New,
    Ready,
    Running,
    Waiting,
    Terminated
};

// Process - Represents a process in the operating system
class Process 
{
    private:
        // Identity
        int pid; // pid - process id
        int arrivalTime; // arrivalTime - time at which process arrives
        int burstTime; // burstTime - time required to complete the process
        int priority; // priority - priority of the process

        // Runtime
        int remainingTime; // remainingTime - time remaining for the process to complete
        ProcessState state; // state - current state of the process
        int startTime; // startTime - time at which process starts
        int completionTime; // completionTime - time at which process completes
        int waitingTime; // waitingTime - time spent waiting in ready queue
        int turnaroundTime; // turnaroundTime - time from arrival to completion
        int responseTime; // responseTime - time from arrival to first execution
    public:
        // Constructor
        Process(int pid, int arrivalTime, int burstTime, int priority);

        // Getters
        int getPid() const;
        int getArrivalTime() const;
        int getBurstTime() const;
        int getPriority() const;

        int getRemainingTime() const;
        ProcessState getState() const;
        int getStartTime() const;
        int getCompletionTime() const;
        int getWaitingTime() const;
        int getTurnaroundTime() const;
        int getResponseTime() const;

        // Setters
        void setRemainingTime(int remainingTime) ;
        void setState(ProcessState state) ;
        void setStartTime(int startTime) ;
        void setCompletionTime(int completionTime) ;
        void setWaitingTime(int waitingTime) ;
        void setTurnaroundTime(int turnaroundTime) ;
        void setResponseTime(int responseTime) ;

};