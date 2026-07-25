/**
 * @file memory.cpp
 * @brief Representation of a single memory partition/block in contiguous memory allocation.
 *
 * CONCEPT:
 *   In contiguous memory allocation, memory is divided into blocks (partitions).
 *   Each block maintains:
 *   - Start Address: The physical memory base location.
 *   - Size: Total bytes/KB in this block.
 *   - Allocated Flag: Whether it is currently assigned to a process (Used vs Free).
 *   - PID: The ID of the process holding this memory block (-1 if free).
 */

#include "memory_manager/memory.h"

Memory::Memory(int startAddress, int size)
    : startAddress(startAddress),
      size(size),
      allocated(false),
      pid(-1)
{
}

// Getters
int Memory::getStartAddress() const { return startAddress; }
int Memory::getSize() const { return size; }
bool Memory::getIsAllocated() const { return allocated; }
int Memory::getPid() const { return pid; }

// Setters
void Memory::setIsAllocated(bool allocated) { this->allocated = allocated; }
void Memory::setPid(int pid) { this->pid = pid; }
void Memory::setSize(int size) { this->size = size; }