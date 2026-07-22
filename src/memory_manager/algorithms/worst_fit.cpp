#include "memory_manager/algorithms/worst_fit.h"

WorstFit::WorstFit(int totalMemory)
    : MemoryManager(totalMemory)
{
}

bool WorstFit::allocate(int pid, int size)
{
    int worstIndex = -1;
    int largestSize = -1;

    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (!blocks[i].getIsAllocated() &&
            blocks[i].getSize() >= size &&
            blocks[i].getSize() > largestSize)
        {
            largestSize = blocks[i].getSize();
            worstIndex = i;
        }
    }

    if (worstIndex == -1)
    {
        return false;
    }

    Memory &block = blocks[worstIndex];

    int startAddress = block.getStartAddress();
    int blockSize = block.getSize();

    block.setIsAllocated(true);
    block.setPid(pid);
    block.setSize(size);

    if (blockSize > size)
    {
        Memory freeBlock(
            startAddress + size,
            blockSize - size);

        blocks.insert(
            blocks.begin() + worstIndex + 1,
            freeBlock);
    }

    return true;
}