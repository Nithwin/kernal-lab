#pragma once

#include "memory_manager/paging/frame.h"
#include "memory_manager/paging/page_table.h"

#include <vector>

class Pager
{
private:
    std::vector<Frame> frames;
    PageTable pageTable;

public:
    Pager(int numberOfFrames, int numberOfPages);

    bool loadPage(int pageNumber);

    const std::vector<Frame>& getFrames() const;

    const PageTable& getPageTable() const;
};