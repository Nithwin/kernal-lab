#include <iostream>
#include <vector>
#include <iomanip>
#include "cpu_scheduler/process.h"
#include "cpu_scheduler/algorithms/fcfs.h"
#include "cpu_scheduler/algorithms/sjf.h"
#include "cpu_scheduler/utils/schedule_printer.h"

int main(){
    std::vector<Process> processes = {
        Process(1, 0, 7, 1),
        Process(2, 2, 4, 1),
        Process(3, 4, 1, 1),
        Process(4, 5, 4, 1)
    };

    SJFScheduler scheduler;
    scheduler.schedule(processes);

    SchedulePrinter::print(processes);
    return 0;
}