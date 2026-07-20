#pragma once

#include <vector>

#include "cpu_scheduler/process.h"

class Scheduler 
{
    public:
        virtual void schedule(std::vector<Process> &processes) = 0;


        virtual ~Scheduler() = default;
};