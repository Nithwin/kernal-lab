#pragma once

#include "cpu_scheduler/scheduler.h"

class RoundRobinScheduler : public Scheduler
{
public:
    explicit RoundRobinScheduler(int quantum);

    void schedule(std::vector<Process>& processes) override;

private:
    int quantum;
};