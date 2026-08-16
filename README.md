# 🛫 Airport Runway Traffic Controller (ATC)

[![Language](https://img.shields.io/badge/Language-C99-00599C.svg?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Data Structure](https://img.shields.io/badge/Data_Structure-Linked_Queue-F7A41D.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/Queue_(abstract_data_type))
[![License](https://img.shields.io/badge/License-MIT-22C55E.svg?style=for-the-badge)](LICENSE)

A command-line based Air Traffic Control (ATC) simulation implemented in pure C. The system models dual-queue scheduling to manage standard runway departures and arrivals while ensuring emergency flights receive strict, preemptive priority clearance using dynamic linked-list queues.

---

## ⚡ Core Architecture

The scheduler operates on a dual-priority First-In, First-Out (FIFO) queue hierarchy:

| Queue | Priority Level | Servicing Order |
| :--- | :--- | :--- |
| **Emergency Queue** | `Level 1 (Highest)` | Preemptively dequeued before standard traffic |
| **Regular Queue** | `Level 2 (Standard)` | Dequeued strictly when the Emergency Queue is empty |

---

## 🧩 Data Structures & Complexity

Memory is dynamically allocated on the heap via `malloc` and cleaned up with `free` upon runway clearance to prevent memory leaks and array overflow limits.

```c
struct FlightNode {
    char flightNumber[16];
    char airline[32];
    struct FlightNode* next;
};

struct FlightQueue {
    struct FlightNode* front;
    struct FlightNode* rear;
};
