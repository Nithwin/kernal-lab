#include "memory_manager/algorithms/next_fit.h"

NextFit::NextFit(int totalMemory)
    : MemoryManager(totalMemory),
      lastIndex(0)
{
}

bool NextFit::allocate(int pid, int size)
{
    if (blocks.empty())
        return false;

    size_t start = lastIndex;
    size_t current = start;

    do
    {
        Memory &block = blocks[current];

        if (!block.getIsAllocated() &&
            block.getSize() >= size)
        {
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
                    blocks.begin() + current + 1,
                    freeBlock);
            }

            lastIndex = current;

            return true;
        }

        current = (current + 1) % blocks.size();

    } while (current != start);

    return false;
}