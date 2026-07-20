#pragma once

#include <vector>

#include "cpu_scheduler/process.h"

class SchedulePrinter
{
public:
    static void print(const std::vector<Process>& processes);
};