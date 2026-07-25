/**
 * @file manager.cpp
 * @brief Base MemoryManager implementation providing block coalescing / deallocation.
 *
 * CONCEPT:
 *   Manages a dynamic linked list / vector of contiguous memory blocks.
 *   Deallocation must handle COALESCING (merging adjacent free memory blocks):
 *   - If block i is freed and block i-1 is also free -> Merge (i-1) and i.
 *   - If block i is freed and block i+1 is also free -> Merge i and (i+1).
 *   - This prevents External Fragmentation from accumulating unnecessarily.
 */

#include "memory_manager/manager.h"

MemoryManager::MemoryManager(int totalMemory) : totalMemory(totalMemory)
{
    // Initialize system memory as one single large unallocated block
    blocks.emplace_back(0, totalMemory);
}

const std::vector<Memory> &MemoryManager::getBlocks() const
{
    return blocks;
}

/**
 * @brief Deallocates memory owned by process PID and merges adjacent free blocks.
 *
 * @param pid Process ID to deallocate.
 * @return true if process was found and freed, false otherwise.
 */
bool MemoryManager::deallocate(int pid)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        Memory &block = blocks[i];

        if (block.getIsAllocated() && block.getPid() == pid)
        {
            // Mark block as free
            block.setIsAllocated(false);
            block.setPid(-1);

            // COALESCING STEP 1: Merge with previous block if it is free
            if (i > 0 && !blocks[i - 1].getIsAllocated())
            {
                blocks[i - 1].setSize(blocks[i - 1].getSize() + block.getSize());
                blocks.erase(blocks.begin() + i);
                i--; // Adjust index after erase
            }

            // COALESCING STEP 2: Merge with next block if it is free
            if (i + 1 < blocks.size() && !blocks[i + 1].getIsAllocated())
            {
                blocks[i].setSize(blocks[i].getSize() + blocks[i + 1].getSize());
                blocks.erase(blocks.begin() + i + 1);
            }

            return true;
        }
    }

    return false;
}