/**
 * @file process.cpp
 * @brief Implementation of the Process class representing an OS Process (PCB).
 *
 * CONCEPT:
 *   In an operating system, every running program is represented by a data structure
 *   called a Process Control Block (PCB). The PCB tracks the process state, CPU time,
 *   memory limits, and timing metrics.
 *
 * TIMING METRICS TRACKED:
 *   - Arrival Time (AT): Time when process enters the Ready Queue.
 *   - Burst Time (BT): Total CPU execution time required.
 *   - Start Time (ST): Time when CPU is first allocated to the process.
 *   - Completion Time (CT): Time when process finishes execution.
 *   - Turnaround Time (TAT) = CT - AT (Total time spent in system).
 *   - Waiting Time (WT) = TAT - BT (Time spent waiting in ready queue).
 *   - Response Time (RT) = ST - AT (Time from arrival to first execution).
 */

#include "cpu_scheduler/process.h"

/**
 * @brief Constructor initializing process identity and runtime state.
 *
 * @param pid Unique process identifier.
 * @param arrivalTime Time at which process arrives in ready queue.
 * @param burstTime Total execution time needed on CPU.
 * @param priority Process priority (lower value = higher priority).
 * @param memorySize Memory footprint required in KB.
 */
Process::Process(
    int pid, int arrivalTime, int burstTime, int priority, int memorySize
) : pid(pid),
    arrivalTime(arrivalTime),
    burstTime(burstTime),
    priority(priority),
    memorySize(memorySize),
    remainingTime(burstTime), // Initially remaining time equals burst time
    state(ProcessState::New),  // Initial state is New
    startTime(-1),             // -1 indicates not yet started
    completionTime(-1),        // -1 indicates not yet completed
    waitingTime(-1),
    turnaroundTime(-1),
    responseTime(-1)
{
}

// ==================== GETTERS ====================

int Process::getPid() const { return pid; }
int Process::getArrivalTime() const { return arrivalTime; }
int Process::getBurstTime() const { return burstTime; }
int Process::getPriority() const { return priority; }
int Process::getMemorySize() const { return memorySize; }

int Process::getRemainingTime() const { return remainingTime; }
ProcessState Process::getState() const { return state; }
int Process::getStartTime() const { return startTime; }
int Process::getCompletionTime() const { return completionTime; }
int Process::getWaitingTime() const { return waitingTime; }
int Process::getTurnaroundTime() const { return turnaroundTime; }
int Process::getResponseTime() const { return responseTime; }

// ==================== SETTERS ====================

void Process::setRemainingTime(int remainingTime) { this->remainingTime = remainingTime; }
void Process::setCompletionTime(int completionTime) { this->completionTime = completionTime; }
void Process::setStartTime(int startTime) { this->startTime = startTime; }
void Process::setState(ProcessState state) { this->state = state; }
void Process::setWaitingTime(int waitingTime) { this->waitingTime = waitingTime; }
void Process::setTurnaroundTime(int turnaroundTime) { this->turnaroundTime = turnaroundTime; }
void Process::setResponseTime(int responseTime) { this->responseTime = responseTime; }
