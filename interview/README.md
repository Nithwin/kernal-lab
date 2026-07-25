# 🎯 OS Interview Questions — Quick Reference

> A curated collection of 60+ interview questions covering all major Operating System topics. Each topic has its own detailed file with comprehensive answers, diagrams, and numerical examples.

---

## 📂 Topic-Wise Question Banks

| # | Topic | Questions | Link |
|---|-------|-----------|------|
| 1 | **General OS Concepts** | 12 Questions | [GENERAL_OS_QA.md](GENERAL_OS_QA.md) |
| 2 | **CPU Scheduling** | 12 Questions | [CPU_SCHEDULING_QA.md](CPU_SCHEDULING_QA.md) |
| 3 | **Memory Management** | 12 Questions | [MEMORY_MANAGEMENT_QA.md](MEMORY_MANAGEMENT_QA.md) |
| 4 | **Process Synchronization** | 12 Questions | [PROCESS_SYNCHRONIZATION_QA.md](PROCESS_SYNCHRONIZATION_QA.md) |
| 5 | **Disk Scheduling** | 12 Questions | [DISK_SCHEDULING_QA.md](DISK_SCHEDULING_QA.md) |

---

## ⚡ Top 10 Most-Asked Questions (Quick Fire)

These are the questions you are **most likely** to get in an interview:

| # | Question | Topic |
|---|----------|-------|
| 1 | What is the difference between a Process and a Thread? | [General](GENERAL_OS_QA.md#q2) |
| 2 | What is a Deadlock? What are the four necessary conditions? | [Sync](PROCESS_SYNCHRONIZATION_QA.md#q4) |
| 3 | What is a Race Condition? How do you prevent it? | [Sync](PROCESS_SYNCHRONIZATION_QA.md#q1) |
| 4 | What is Virtual Memory? | [Memory](MEMORY_MANAGEMENT_QA.md#q7) |
| 5 | What is Paging? How does address translation work? | [Memory](MEMORY_MANAGEMENT_QA.md#q3) |
| 6 | Compare FCFS, SJF, SRTF, Priority, and Round Robin. | [CPU](CPU_SCHEDULING_QA.md#q8) |
| 7 | What is a Page Fault? What happens when one occurs? | [Memory](MEMORY_MANAGEMENT_QA.md#q5) |
| 8 | What is the difference between a Mutex and a Semaphore? | [Sync](PROCESS_SYNCHRONIZATION_QA.md#q3) |
| 9 | What is Thrashing? | [Memory](MEMORY_MANAGEMENT_QA.md#q8) |
| 10 | Explain the Producer-Consumer problem. | [Sync](PROCESS_SYNCHRONIZATION_QA.md#q7) |

---

## 💡 Interview Tips

1. **Always draw diagrams** — Interviewers love Gantt charts, memory maps, and state diagrams.
2. **Know the trade-offs** — Every algorithm has pros and cons. Say both.
3. **Be ready for numericals** — Practice calculating WT, TAT, and head movements by hand.
4. **Connect to real systems** — Mention that Linux uses CFS, that SSDs make disk scheduling less relevant, etc.
5. **Understand the code** — If asked to implement, the C++ code in this repo is interview-ready.

---

## 🏢 Where These Questions Are Asked

| Company | Common Focus Areas |
|---------|-------------------|
| **Google** | Process/Thread, Synchronization, Virtual Memory |
| **Amazon** | Deadlocks, Scheduling, IPC |
| **Microsoft** | Memory Management, Paging, System Calls |
| **Apple** | Scheduling, Synchronization Primitives |
| **FAANG (General)** | All of the above + Numericals |
| **University Exams** | Everything with heavy focus on numericals |
