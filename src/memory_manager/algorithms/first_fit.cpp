/**
 * @file first_fit.cpp
 * @brief First-Fit Contiguous Memory Allocation Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Scans memory blocks from the beginning (index 0).
 *   - Allocates the process in the VERY FIRST unallocated block that is large enough.
 *   - If the chosen block is larger than required, it splits the block into:
 *       1. Allocated block of requested size.
 *       2. Remaining smaller free block (leftover space).
 *
 * PROS: Fast execution (stops at first match).
 * CONS: Leaves small unusable holes near the beginning of memory over time.
 */

#include "memory_manager/algorithms/first_fit.h"

FirstFit::FirstFit(int totalMemory)
    : MemoryManager(totalMemory)
{
}

bool FirstFit::allocate(int pid, int size)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        // Check if block is free and large enough
        if (!blocks[i].getIsAllocated() && blocks[i].getSize() >= size)
        {
            int startAddress = blocks[i].getStartAddress();
            int blockSize = blocks[i].getSize();

            // Allocate requested portion
            blocks[i].setIsAllocated(true);
            blocks[i].setPid(pid);
            blocks[i].setSize(size);

            // Split block if there is leftover space
            if (blockSize > size)
            {
                Memory freeBlock(startAddress + size, blockSize - size);
                blocks.insert(blocks.begin() + i + 1, freeBlock);
            }

            return true;
        }
    }
    return false; // Out of memory or no single block large enough
}
