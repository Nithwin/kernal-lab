/**
 * @file worst_fit.cpp
 * @brief Worst-Fit Contiguous Memory Allocation Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Scans ALL free memory blocks in the system.
 *   - Allocates the process into the LARGEST available free block.
 *
 * RATIONALE:
 *   - The idea is that splitting a large block leaves a large remaining free block,
 *     which may be useful for subsequent allocations.
 *
 * CONS: Quickly destroys large contiguous blocks, leaving no large blocks for big requests later.
 */

#include "memory_manager/algorithms/worst_fit.h"

WorstFit::WorstFit(int totalMemory)
    : MemoryManager(totalMemory)
{
}

bool WorstFit::allocate(int pid, int size)
{
    int worstIndex = -1;
    int largestSize = -1;

    // Find the largest unallocated block
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

    // Split leftover space into a free block
    if (blockSize > size)
    {
        Memory freeBlock(startAddress + size, blockSize - size);
        blocks.insert(blocks.begin() + worstIndex + 1, freeBlock);
    }

    return true;
}