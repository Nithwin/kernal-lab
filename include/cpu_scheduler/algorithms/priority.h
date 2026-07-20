#pragma once

#include "cpu_scheduler/scheduler.h"

class PriorityScheduler : public Scheduler
{
public:
    void schedule(std::vector<Process> &processes) override;
};