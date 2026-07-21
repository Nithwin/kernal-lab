#pragma once

#include <vector>

#include "memory_manager/memory.h"

class MemoryPrinter
{
public:
    static void print(const std::vector<Memory>& blocks);
};