#include <iostream>
#include <vector>
#include <iomanip>
#include "cpu_scheduler/process.h"
#include "cpu_scheduler/algorithms/fcfs.h"
#include "cpu_scheduler/algorithms/sjf.h"
#include "cpu_scheduler/algorithms/srtf.h"
#include "cpu_scheduler/algorithms/priority.h"
#include "cpu_scheduler/utils/schedule_printer.h"

int main()
{
    std::vector<Process> processes = {
        Process(1, 0, 5, 3),
        Process(2, 1, 4, 1),
        Process(3, 2, 2, 2)};

    PriorityScheduler scheduler;
    scheduler.schedule(processes);

    SchedulePrinter::print(processes);
    return 0;
}