#include "cpu_scheduler/process.h"

Process::Process(
    int pid, int arrivalTime, int burstTime, int priority
) : pid(pid),
    arrivalTime(arrivalTime),
    burstTime(burstTime),
    priority(priority),
    remainingTime(burstTime),
    state(ProcessState::New),
    startTime(-1),
    completionTime(-1),
    waitingTime(-1),
    turnaroundTime(-1),
    responseTime(-1)
    {
        
    }

// Getters Functions
int Process::getPid() const 
{
    return pid;
}

int Process::getArrivalTime() const 
{
    return arrivalTime;
}

int Process::getBurstTime() const 
{
    return burstTime;
}

int Process::getPriority() const 
{
    return priority;
}

int Process::getRemainingTime() const 
{
    return remainingTime;
}

ProcessState Process::getState() const 
{
    return state;
}

int Process::getStartTime() const 
{
    return startTime;
}

int Process::getCompletionTime() const 
{
    return completionTime;
}

int Process::getWaitingTime() const {
    return waitingTime;
}

int Process::getTurnaroundTime() const {
    return turnaroundTime;
}

int Process::getResponseTime() const {
    return responseTime;
}


void Process::setRemainingTime(int remainingTime)  
{
    this->remainingTime = remainingTime;
}

void Process::setCompletionTime(int completionTime)  
{
    this->completionTime = completionTime;
}

void Process::setStartTime(int startTime)  
{
    this->startTime = startTime;
}

void Process::setState(ProcessState state)  
{
    this->state = state;
}

void Process::setWaitingTime(int waitingTime) {
    this->waitingTime = waitingTime;
}

void Process::setTurnaroundTime(int turnaroundTime) {
    this->turnaroundTime = turnaroundTime;
}

void Process::setResponseTime(int responseTime) {
    this->responseTime = responseTime;
}

