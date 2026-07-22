#pragma once

#include "memory_manager/manager.h"

class NextFit : public MemoryManager
{
private:
    size_t lastIndex;

public:
    NextFit(int totalMemory);

    bool allocate(int pid, int size) override;
};