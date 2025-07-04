# 📘 Chapter 6 – Advanced Process Management (Summary)
**From _Linux System Programming_ by Robert Love, 2nd Ed.**

---

## 🔄 Process Scheduling
- The kernel scheduler selects **runnable processes** (those not blocked on I/O, etc.).
- Goals: **maximize CPU utilization**, minimize wait time, and ensure fairness :contentReference[oaicite:1]{index=1}.
- Covers **preemptive scheduling**, **timeslices**, and the Linux **Completely Fair Scheduler (CFS)**.
- Explains **processor affinity** and CPU sets: binding processes to specific CPUs for cache performance :contentReference[oaicite:2]{index=2}.

## 🧭 Yielding the Processor
- `sched_yield()` lets a running process give up the CPU voluntarily.
- Useful in busy-wait loops or when expecting immediate CPU from others :contentReference[oaicite:3]{index=3}.

## 🎚️ Priorities & Nice Values
- Processes can adjust their priority using **`nice()`**, where lower nice = higher priority.
- Real-time scheduling policies (`SCHED_FIFO`, `SCHED_RR`) grant stronger priority guarantees for time-sensitive tasks :contentReference[oaicite:4]{index=4}.

## 🧠 Processor Affinity
- **Get/set CPU affinity** with `sched_getaffinity()` and `sched_setaffinity()`.
- Ensures cache affinity, reducing context-switch overhead :contentReference[oaicite:5]{index=5}.

## ⏱️ Real-Time Scheduling
- Differences between **hard** and **soft real-time** systems.
- Configurable policies: `SCHED_FIFO`, `SCHED_RR`, with real-time priority range 0–99 :contentReference[oaicite:6]{index=6}.
- Care needed: real-time tasks can lead to starvation of normal tasks.

## 🔒 Resource Limits
- Kernel enforces per-process limits via `setrlimit()`/`getrlimit()`:
  - CPU usage (`RLIMIT_CPU`)
  - File sizes (`RLIMIT_FSIZE`)
  - Number of open files, memory, etc. :contentReference[oaicite:7]{index=7}.
- Helps contain rogue or misbehaving processes, essential for robustness.

---

## ✅ Why It Matters
Advanced control over process scheduling, priorities, affinity, and resource limits is critical for writing:
- Real-time or latency-sensitive applications
- High-performance servers that benefit from core binding
- Robust daemons that avoid resource exhaustion

This chapter equips systems programmers with the tools to finely tune how tasks interact with the kernel scheduler and manage system impact.

---

## 📚 References
- *Linux System Programming*, 2nd Ed. — Robert Love  
- `man 2 sched_setscheduler`, `man 2 setrlimit`, `man 2 sched_getaffinity`  
- Wikipedia: [Completely Fair Scheduler](https://en.wikipedia.org/wiki/Completely_Fair_Scheduler) :contentReference[oaicite:8]{index=8}

