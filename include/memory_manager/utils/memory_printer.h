#pragma once

#include <vector>

#include "memory_manager/memory.h"
#include "memory_manager/paging/pager.h"

class MemoryPrinter
{
public:
    static void print(const std::vector<Memory>& blocks);
    static void page_print(const Pager& pager);
};