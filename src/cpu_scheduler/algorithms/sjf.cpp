#include "cpu_scheduler/algorithms/sjf.h"

#include <algorithm>

void SJFScheduler::schedule(std::vector<Process>& processes)
{
    if (processes.empty())
    {
        return;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while(completedProcesses < processes.size())
    {
        Process *selectedProcess = nullptr;

        for(Process& process: processes) 
        {
            // We ignore the completed process
            if(process.getState() == ProcessState::Terminated)
            {
                continue;
            } 

            // If the process didn't arrive we simple skip it
            if(process.getArrivalTime() > currentTime)
            {
                continue;
            }

            // Since our selectedProcess will be at 'nullptr' at beginning we keep the 
            // first process we find
            if(selectedProcess == nullptr)
            {
                selectedProcess = &process;
            } else if(process.getBurstTime() == selectedProcess->getBurstTime())
            {
                if(process.getArrivalTime() == selectedProcess->getArrivalTime()){
                    if(process.getPid() < selectedProcess->getPid()){
                        selectedProcess = &process;
                    }
                } else if(process.getArrivalTime() < selectedProcess->getArrivalTime()){
                    selectedProcess = &process;
                }
            }
            else if(process.getBurstTime() < selectedProcess->getBurstTime()) 
            {   // We choose the process which has less burstTime (which mean time needed to finish the job)
                selectedProcess = &process;
            } 

        }

        // If no process selected means no process arrived yet so we just skip the time
        if(selectedProcess == nullptr){
            currentTime++;
            continue;
        }

        // Starting the Process
        selectedProcess->setStartTime(currentTime);
        selectedProcess->setState(ProcessState::Running);

        // Executing the Process
        currentTime += selectedProcess->getBurstTime();

        // Completing the Process
        selectedProcess->setCompletionTime(currentTime);
        selectedProcess->setRemainingTime(0);
        selectedProcess->setState(ProcessState::Terminated);


        // Calculate metrics
        // Time taken to perform the job
        int turnaroundTime = selectedProcess->getCompletionTime() - selectedProcess->getArrivalTime();
        selectedProcess->setTurnaroundTime(turnaroundTime);

        int waitingTime = turnaroundTime - selectedProcess->getBurstTime();
        selectedProcess->setWaitingTime(waitingTime);

        int responseTime = selectedProcess->getStartTime() - selectedProcess->getArrivalTime();
        selectedProcess->setResponseTime(responseTime);

        completedProcesses++;
    }
}