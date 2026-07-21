#pragma once
#include <vector>
#include "memory_manager/memory.h"

class MemoryManager
{
protected:
    int totalMemory;
    std::vector<Memory> blocks;

public:
    MemoryManager(int totalMemory);

    virtual bool allocate(int pid, int size) = 0;

    virtual ~MemoryManager() = default;
};