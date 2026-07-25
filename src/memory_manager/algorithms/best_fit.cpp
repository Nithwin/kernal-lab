/**
 * @file best_fit.cpp
 * @brief Best-Fit Contiguous Memory Allocation Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Scans ALL free memory blocks in the system.
 *   - Allocates process into the SMALLEST free block that is large enough (>= requested size).
 *
 * PROS: Leaves maximum space available in larger blocks for future big requests.
 * CONS: Can produce tiny, unusable memory fragments (severe internal/external fragmentation).
 *       Requires traversing the entire list of blocks (slower search).
 */

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

    // Scan all blocks to find the tightest fit
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

    // No suitable block found
    if (bestIndex == -1)
    {
        return false;
    }

    Memory& block = blocks[bestIndex];
    int startAddress = block.getStartAddress();
    int blockSize = block.getSize();

    // Allocate best block
    block.setIsAllocated(true);
    block.setPid(pid);
    block.setSize(size);

    // Split leftover space into a new free block
    if (blockSize > size)
    {
        Memory freeBlock(startAddress + size, blockSize - size);
        blocks.insert(blocks.begin() + bestIndex + 1, freeBlock);
    }

    return true;
}