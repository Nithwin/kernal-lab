#include "memory_manager/manager.h"

MemoryManager::MemoryManager(int totalMemory) : totalMemory(totalMemory)
{
    blocks.emplace_back(0, totalMemory);
}

const std::vector<Memory> &MemoryManager::getBlocks() const
{
    return blocks;
}

bool MemoryManager::deallocate(int pid)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        Memory &block = blocks[i];

        if (block.getIsAllocated() && block.getPid() == pid)
        {
            block.setIsAllocated(false);
            block.setPid(-1);

            if (i > 0 && !blocks[i - 1].getIsAllocated())
            {
                blocks[i - 1].setSize(
                    blocks[i - 1].getSize() + block.getSize());

                blocks.erase(blocks.begin() + i);

                i--;
            }

            if (i + 1 < blocks.size() && !blocks[i + 1].getIsAllocated())
            {
                blocks[i].setSize(
                    blocks[i].getSize() + blocks[i + 1].getSize());

                blocks.erase(blocks.begin() + i + 1);
            }

            return true;
        }
    }

    return false;
}