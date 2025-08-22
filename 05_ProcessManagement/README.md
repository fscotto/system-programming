# 📘 Chapter 5 – Process Management (Summary)
**Based on _Linux System Programming_ by Robert Love**

This chapter covers how Linux manages processes, including their creation, execution, and termination. It introduces key system calls and concepts that underpin multitasking and process control in Unix-like systems.

---

## 🧠 Core Concepts
- A **process** is an independent program with its own memory and execution context.
- The kernel provides **process abstraction** to manage concurrency.
- Processes are scheduled and isolated using virtual memory and process control blocks (PCBs).

---

## 🛠️ Process Creation & Termination
- `fork()` creates a new process (child) by duplicating the calling (parent) process using **copy-on-write**.
- `exec()` replaces the current process image with a new program.
- `wait()` and `waitpid()` allow the parent to wait for and collect the child’s exit status.
- `exit()` performs cleanup and exits the process gracefully.
- `_exit()` exits immediately without flushing stdio buffers.

---

## 🔍 Signals & Zombies
- **Zombie processes** occur when a child exits but the parent doesn’t read its status with `wait()`.
- `SIGCHLD` is sent to the parent when a child terminates.
- The `init` process (PID 1) will adopt and clean up orphaned children.

---

## 👥 Process Hierarchies
- Every process has a unique **PID** and a **PPID** (parent PID).
- Together they form a **process tree**, starting from `init`.
- Tools like `ps`, `pstree`, and `/proc` are useful for visualizing process hierarchies.

---

## 🎯 Process Identifiers & Groups
- `getpid()` returns the process’s ID.
- `getppid()` returns the parent’s ID.
- **Process groups** and **sessions** enable job control, allowing signals to be sent to multiple related processes.

---

## 🧩 Resource Cleanup
- On termination, the kernel reclaims:
  - Memory
  - Open file descriptors
  - IPC resources
- `exit()` also triggers:
  - `atexit()` handlers
  - Standard I/O flushes
  - Potential creation of core dumps (if enabled)

---

## ✅ Why This Matters
A strong understanding of process control is essential for:
- Writing daemons
- Managing background jobs
- Building shells or supervisors
- Avoiding resource leaks and zombie processes

---

## 📚 References
- _Linux System Programming_, 2nd Edition by Robert Love (O'Reilly)
- `man 2 fork`, `man 2 execve`, `man 2 wait`, `man 2 exit`, `man 7 signal`

---

*This summary is for educational purposes.*

