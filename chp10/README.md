# Chapter 10 – Signals (Summary)

**Based on _Linux System Programming, 2nd Edition_ by Robert Love**  
This chapter dives into the mechanics, pitfalls, and POSIX-compliant interfaces of signals in Linux.

---

## What Are Signals?

- **Signals** are asynchronous software interrupts used for interprocess communication (IPC). They notify processes of events such as:
  - User-generated events (e.g., pressing Ctrl‑C sends **SIGINT**)
  - Internal faults (e.g., divide by zero triggers **SIGFPE**)
  - Kernel actions or process-related events (e.g., child termination sends **SIGCHLD**)
- Signals require special handling because they can occur at any moment, disrupting normal flow.

---

## Signal Handling Models

- Early Unix systems struggled with **unreliable signals**—deliveries could be missed or lost.
- **POSIX** standardized a **reliable signal model**, ensuring signals are not lost and behavior is predictable.

---

## Setting Signal Handlers

- Use the **`sigaction()`** interface (preferred) to set up handlers in a robust and portable way.
- `signal()` is outdated and has inconsistent behavior across platforms; use only for trivial cases like ignoring or using the default handler.
- **SIGKILL** and **SIGSTOP** cannot be caught, ignored, or blocked.

---

## Signal Masks and Blocking

- Each process has a **signal mask** (via `sigset_t`) that defines which signals are currently blocked.
- Signal blocking is essential when running critical code to avoid race conditions.
- Use `sigprocmask()` to modify the mask safely.

---

## Common Signal APIs

```c
int kill(pid_t pid, int signo);   // Send a signal to another process
int killpg(int pgrp, int signo);  // Send a signal to all processes in a given process group. Equivalent to kill(-pgrp, signo).
int raise(int signo);             // Send a signal to self
unsigned int alarm(unsigned int seconds); // Schedule a SIGALRM
int pause(void);                  // Wait indefinitely until a signal arrives
void abort(void);                 // Raise SIGABRT and terminate
```

These calls allow fine-grained control over signal generation and handling.

---

## Reentrancy and Safe Signal Handling

- Signal handlers can interrupt your program at any point, even in the middle of non-reentrant functions, causing undefined behavior.
- Only call **async-signal-safe** functions within handlers (e.g., `write`, `_exit`).
- Avoid unsafe operations like `malloc()`, `printf()`, or `strtok()` inside signal handlers.

---

## Process Behavior with Signals

- Signal dispositions are inherited across `fork()` (child inherits parent’s handlers) but reset to default on `exec()`.

---

## Summary of Key Concepts

| Concept                  | Description                                                |
|--------------------------|------------------------------------------------------------|
| Signals                  | Asynchronous notifications from kernel or processes        |
| POSIX Signal Model       | Reliable, standardized approach to signal delivery        |
| `sigaction()`            | Robust interface to set signal handlers                    |
| Signal Masks             | Block/unblock signals to prevent interruptions             |
| Async-signal-safe calls  | Safe functions to call inside signal handlers              |
| Core Functions           | `kill`, `raise`, `alarm`, `pause`, `abort`                 |

---

## Why This Matters

Signals are indispensable for handling asynchronous events, timed operations, and interprocess interactions. Proper use of reliable signal handling, blocking, and safe coding practices ensures your applications remain responsive and stable under interruptions.

---

## References  

- _Linux System Programming_ by Robert Love (2nd Ed.) — Chapter 10  
- POSIX and Linux signal handling docs: `signal()`, `sigaction()`, `sigprocmask()`
