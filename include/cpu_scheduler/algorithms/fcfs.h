#pragma once

#include "cpu_scheduler/scheduler.h"

class FCFSScheduler : public Scheduler 
{
    public:
        void schedule(std::vector<Process> &processes) override;
};