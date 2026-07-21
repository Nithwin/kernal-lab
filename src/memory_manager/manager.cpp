#include "memory_manager/manager.h"

MemoryManager::MemoryManager(int totalMemory) :
totalMemory(totalMemory)
{
    blocks.emplace_back(0, totalMemory);
}