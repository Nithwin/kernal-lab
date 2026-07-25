cmake_minimum_required(VERSION 3.20)

project(KernelLab VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Threading is required for synchronization modules
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(include)

# Module 1: CPU Scheduling Tests
add_executable(test_cpu_scheduler
    tests/test_cpu_scheduler.cpp
    src/cpu_scheduler/process.cpp
    src/cpu_scheduler/scheduler.cpp
    src/cpu_scheduler/algorithms/fcfs.cpp
    src/cpu_scheduler/algorithms/sjf.cpp
    src/cpu_scheduler/algorithms/srtf.cpp
    src/cpu_scheduler/algorithms/priority.cpp
    src/cpu_scheduler/algorithms/round_robin.cpp
    src/cpu_scheduler/utils/schedule_printer.cpp
)

# Module 2: Memory Management Tests
add_executable(test_memory_manager
    tests/test_memory_manager.cpp
    src/cpu_scheduler/process.cpp
    src/memory_manager/memory.cpp
    src/memory_manager/manager.cpp
    src/memory_manager/algorithms/first_fit.cpp
    src/memory_manager/algorithms/best_fit.cpp
    src/memory_manager/algorithms/next_fit.cpp
    src/memory_manager/algorithms/worst_fit.cpp
    src/memory_manager/utils/memory_printer.cpp
    src/memory_manager/paging/pager.cpp
    src/memory_manager/paging/page.cpp
    src/memory_manager/paging/page_table.cpp
    src/memory_manager/paging/frame.cpp
)

# Module 6: Disk Scheduling Tests
add_executable(test_disk_scheduling
    tests/test_disk_scheduling.cpp
    src/disk_scheduling/algorithms/fcfs.cpp
    src/disk_scheduling/algorithms/sstf.cpp
    src/disk_scheduling/algorithms/scan.cpp
    src/disk_scheduling/algorithms/c_scan.cpp
)

# Module 3: Synchronization Tests (Separate executables as each has a main())
add_executable(test_sync_dining src/synchronization/dining_philosophers.cpp)
target_link_libraries(test_sync_dining PRIVATE Threads::Threads)

add_executable(test_sync_mutex src/synchronization/mutex_demo.cpp)
target_link_libraries(test_sync_mutex PRIVATE Threads::Threads)

add_executable(test_sync_producer src/synchronization/producer_consumer.cpp)
target_link_libraries(test_sync_producer PRIVATE Threads::Threads)

add_executable(test_sync_semaphore src/synchronization/semaphore_demo.cpp)
target_link_libraries(test_sync_semaphore PRIVATE Threads::Threads)