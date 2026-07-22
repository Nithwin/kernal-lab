#pragma once

#include "memory_manager/manager.h"

class WorstFit : public MemoryManager
{
public:
    WorstFit(int totalMemory);

    bool allocate(int pid, int size) override;
};