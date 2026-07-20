#include "cpu_scheduler/algorithms/srtf.h"

void SRTFScheduler::schedule(std::vector<Process> &processes)
{
    if (processes.empty())
    {
        return;
    }

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < processes.size())
    {
        Process *selectedProcess = nullptr;

        for (Process &process : processes)
        {
            if (process.getState() == ProcessState::Terminated)
            {
                continue;
            }
            if (process.getArrivalTime() > currentTime)
            {
                continue;
            }

            if (selectedProcess == nullptr)
            {
                selectedProcess = &process;
            }
            else if (process.getRemainingTime() == selectedProcess->getRemainingTime())
            {
                if (process.getArrivalTime() == selectedProcess->getArrivalTime())
                {
                    if (process.getPid() < selectedProcess->getPid())
                    {
                        selectedProcess = &process;
                    }
                }
                else if (process.getArrivalTime() < selectedProcess->getArrivalTime())
                {
                    selectedProcess = &process;
                }
            }

            else if (selectedProcess->getRemainingTime() > process.getRemainingTime())
            {
                selectedProcess = &process;
            }
        }

        if (selectedProcess == nullptr)
        {
            currentTime++;
            continue;
        }

        startProcess(*selectedProcess, currentTime);

        selectedProcess->setRemainingTime(selectedProcess->getRemainingTime() - 1);

        currentTime++;

        if (selectedProcess->getRemainingTime() == 0)
        {
            finishProcess(*selectedProcess, currentTime);

            completedProcesses++;
        }
        else
        {
            selectedProcess->setState(ProcessState::Ready);
        }
    }
}