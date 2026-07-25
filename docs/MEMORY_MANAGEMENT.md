# Memory Management Module

This module focuses on how the Operating System manages main memory (RAM).

## Features

### 1. Contiguous Memory Allocation
Allocates continuous blocks of memory to processes.
- **First Fit:** Allocates the first hole that is big enough.
- **Best Fit:** Allocates the smallest hole that is big enough, minimizing wasted space.
- **Worst Fit:** Allocates the largest hole, leaving behind a potentially useful large hole.
- **Next Fit:** Similar to First Fit, but starts searching from the location of the last allocation.

### 2. Paging
A non-contiguous memory management technique.
- Divides logical memory into blocks of same size called **Pages**.
- Divides physical memory into fixed-sized blocks called **Frames**.
- Uses a **Page Table** to map logical pages to physical frames.

## C++ Implementation Details
- Uses abstract interfaces for allocators.
- Pager classes handle the complex mappings between pages and frames.
- See `tests/test_memory_manager.cpp` for a complete example of allocating processes into frames using a `Pager`.
