#pragma once

#include <vector>

#include "cpu_scheduler/process.h"

class Scheduler 
{
    public:
        virtual void schedule(std::vector<Process> &processes) = 0;


        virtual ~Scheduler() = default;
        
    protected:
    void startProcess(Process& process, int currentTime);

    void finishProcess(Process& process, int currentTime);
};