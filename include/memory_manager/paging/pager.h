#pragma once

#include "cpu_scheduler/process.h"
#include "memory_manager/paging/frame.h"
#include "memory_manager/paging/page_table.h"

#include <unordered_map>
#include <vector>

class Pager
{
private:
    int pageSize;

    std::vector<Frame> frames;
    std::unordered_map<int, PageTable> pageTables;

    Frame* findFreeFrame();

public:
    Pager(int numberOfFrames, int pageSize);

    bool loadProcess(const Process& process);

    bool deallocateProcess(int pid);

    const std::vector<Frame>& getFrames() const;

    const std::unordered_map<int, PageTable>& getPageTables() const;
};