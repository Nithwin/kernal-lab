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
        const int pid; // pid - process id
        const int arrivalTime; // arrivalTime - time at which process arrives
        const int burstTime; // burstTime - time required to complete the process
        const int priority; // priority - priority of the process

        // Runtime
        int remainingTime; // remainingTime - time remaining for the process to complete
        ProcessState state; // state - current state of the process
        int startTime; // startTime - time at which process starts
        int completionTime; // completionTime - time at which process completes
    public:
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

        // Setters
        void setRemainingTime(int remainingTime) ;
        void setState(ProcessState state) ;
        void setStartTime(int startTime) ;
        void setCompletionTime(int completionTime) ;

};