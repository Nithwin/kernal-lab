/**
 * @file next_fit.cpp
 * @brief Next-Fit Contiguous Memory Allocation Algorithm.
 *
 * ALGORITHM CONCEPT:
 *   - Variation of First-Fit.
 *   - Begins scanning from the block index where the LAST successful allocation occurred
 *     (using a circular pointer/index `lastIndex`).
 *   - Wraps around to index 0 if it reaches the end of the memory array.
 *
 * PROS: Avoids concentrating allocations at the beginning of memory (spreads allocations out).
 * CONS: Can break up large free blocks at the end of memory faster than First-Fit.
 */

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

    // Circular traversal starting from lastIndex
    do
    {
        Memory &block = blocks[current];

        if (!block.getIsAllocated() && block.getSize() >= size)
        {
            int startAddress = block.getStartAddress();
            int blockSize = block.getSize();

            block.setIsAllocated(true);
            block.setPid(pid);
            block.setSize(size);

            if (blockSize > size)
            {
                Memory freeBlock(startAddress + size, blockSize - size);
                blocks.insert(blocks.begin() + current + 1, freeBlock);
            }

            // Update lastIndex pointer for next allocation call
            lastIndex = current;

            return true;
        }

        // Advance to next block in circular fashion
        current = (current + 1) % blocks.size();

    } while (current != start); // Stop when full loop completed

    return false; // No suitable block found
}