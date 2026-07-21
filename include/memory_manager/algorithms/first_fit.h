#pragma once

#include "memory_manager/manager.h"

class FirstFit : public MemoryManager
{
public:
    FirstFit(int totalMemory);

    bool allocate(int pid, int size) override;
};