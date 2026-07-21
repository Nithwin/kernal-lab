#include "memory_manager/algorithms/first_fit.h"

FirstFit::FirstFit(int totalMemory)
    : MemoryManager(totalMemory)
{
}

bool FirstFit::allocate(int pid, int size)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (!blocks[i].getIsAllocated() && blocks[i].getSize() >= size)
        {
            int startAddress = blocks[i].getStartAddress();
            int blockSize = blocks[i].getSize();
            blocks[i].setIsAllocated(true);
            blocks[i].setPid(pid);
            blocks[i].setSize(size);

            if (blockSize > size)
            {
                Memory freeBlock(startAddress + size, blockSize - size);
                blocks.insert(blocks.begin() + i + 1, freeBlock);
            }

            return true;
        }
    }
    return false;
}

