# Chapter 1 – Introduction and Core Concepts

## 🔧 What is System Programming?
- Low-level programming that interacts directly with the **kernel** and system libraries via **system calls**, typically written in **C**.
- Includes shell tools (bash, gcc, coreutils), daemons, webservers, etc.

## Why Learn It?
- Even in high-level environments (JS, Java, Python), understanding internal mechanisms leads to better, more efficient code.
- Still essential for core components of Linux systems: kernel, drivers, glibc, gcc.

## Core Elements
1. **System calls** – entry points from user process to the kernel (e.g., `read()`, `write()`).
2. **C Library** (glibc) – interface between user programs and system calls.
3. **C Compiler** (gcc) – handles APIs, ABIs, and object formats.

## API vs ABI
- **API**: interface at the source code level (e.g., libc functions).
- **ABI**: binary layout and conventions (e.g., syscall invocation, parameter ordering). Defines compatibility between systems and architectures.

## Standards and Compatibility
- POSIX/SUS as a reference, but Linux is not officially certified.
- The **Linux Standard Base (LSB)** initiative extends POSIX/SUS to ensure binary compatibility across distributions.

## Linux Basics
- **Files**: name + inode, represented by **file descriptors** (int). Linear byte streams (no formatting).
- **Processes**: entities with address space, pid, users, groups, permissions, signals.
- **IPC**: inter-process communication mechanisms (pipe, FIFO, socket, shared memory, semaphores).
- **Error handling**: functions return values and set `errno`. Useful functions: `perror()`, `strerror()`, `strerror_r()`.
