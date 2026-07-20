#pragma once

#include "cpu_scheduler/scheduler.h"

class SJFScheduler : public Scheduler 
{
    public:
        void schedule(std::vector<Process> &processes) override;
};