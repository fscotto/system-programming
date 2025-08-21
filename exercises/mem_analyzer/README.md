# 🧠 Memory Management Analyzer

This project demonstrates how different memory allocation methods (`malloc`, `calloc`, and `mmap`) perform in terms of speed and memory usage in a simulated workload.

---

## 📜 Description
The program dynamically allocates and frees memory blocks of varying sizes, measuring:

- Allocation and deallocation times.
- Memory usage via `/proc/self/status` or `/proc/self/statm`.
- Peak memory consumption during execution.

It produces a report comparing performance across allocation methods.

---

## 🚀 Features
- **Dynamic Allocation Testing** – compares `malloc`, `calloc`, and `mmap`.
- **Performance Metrics** – measures allocation/deallocation times.
- **Memory Usage Tracking** – monitors real-time process memory usage.
- **Optional Memory Leak Simulation** – detects unfreed memory using Valgrind.
- **CLI Mode Selection** – choose allocator at runtime (`--malloc`, `--calloc`, `--mmap`).

---

## 🛠️ Build
```bash
make
```

---

## ▶️ Run
```bash
./mem_analyzer --malloc
./mem_analyzer --calloc
./mem_analyzer --mmap
```

---

## 🧪 Test & Debug
```bash
make valgrind
```

---

## 📊 Example Output
```
Allocator: malloc
Blocks: 10000
Average Allocation Time: 0.24 μs
Average Free Time: 0.18 μs
Peak Memory Usage: 2.5 MB
```

---

## 📂 Project Structure
```
mem_analyzer/
 ├── README.md
 ├── Makefile
 └── main.c
```

---

## 🔍 Learning Objectives
- Understand differences between `malloc`, `calloc`, and `mmap`.
- Learn to measure memory usage through `/proc`.
- Practice debugging memory errors with Valgrind.
- Gain insight into memory allocation strategies in Linux.

---
