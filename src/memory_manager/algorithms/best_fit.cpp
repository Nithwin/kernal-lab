#include "memory_manager/algorithms/best_fit.h"

#include <limits>

BestFit::BestFit(int totalMemory)
    : MemoryManager(totalMemory)
{
}

bool BestFit::allocate(int pid, int size)
{
    int bestIndex = -1;
    int smallestSize = std::numeric_limits<int>::max();

    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (!blocks[i].getIsAllocated() &&
            blocks[i].getSize() >= size &&
            blocks[i].getSize() < smallestSize)
        {
            smallestSize = blocks[i].getSize();
            bestIndex = i;
        }
    }

    if (bestIndex == -1)
    {
        return false;
    }

    Memory& block = blocks[bestIndex];

    int startAddress = block.getStartAddress();
    int blockSize = block.getSize();

    block.setIsAllocated(true);
    block.setPid(pid);
    block.setSize(size);

    if (blockSize > size)
    {
        Memory freeBlock(startAddress + size, blockSize - size);
        blocks.insert(blocks.begin() + bestIndex + 1, freeBlock);
    }

    return true;
}