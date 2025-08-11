# Chapter 9 - Memory Management

This document summarizes the key concepts from **Chapter 9: Memory Management** in *Linux System Programming, 2nd Edition* by Robert Love.

---

## Overview

Memory management in Linux involves allocating, using, and freeing memory efficiently while avoiding leaks and fragmentation. This chapter explains how user-space programs interact with the kernel’s memory manager through system calls, library functions, and advanced allocation techniques.

---

## Key Topics

### 1. Memory Layout of a Process

A typical Linux process memory layout includes:

- **Text Segment** – Executable code of the program (read-only).
- **Data Segment** – Initialized global and static variables.
- **BSS Segment** – Uninitialized global and static variables.
- **Heap** – Dynamically allocated memory (via `malloc`, `calloc`, `realloc`).
- **Stack** – Function call frames, local variables.
- **Memory Mappings** – Shared libraries, `mmap` allocations, etc.

---

### 2. Dynamic Memory Allocation

- **malloc(size_t size)** – Allocates memory but leaves it uninitialized.
- **calloc(size_t nmemb, size_t size)** – Allocates and zeroes memory.
- **realloc(void *ptr, size_t size)** – Resizes a previously allocated block.
- **free(void *ptr)** – Frees allocated memory.

#### Common pitfalls

- **Memory leaks** – Forgetting to free memory.
- **Double free** – Calling `free` twice on the same pointer.
- **Use-after-free** – Accessing memory after it has been freed.

---

### 3. `brk` and `sbrk`

- Low-level system calls to manage the program break (end of the data segment).
- Rarely used directly; `malloc` and friends handle these internally.

---

### 4. Memory Mapping with `mmap`

- **mmap()** maps files or anonymous memory into the process address space.
- Advantages:
  - Direct file access without extra copy operations.
  - Efficient large memory allocations.
- Common use cases:
  - Loading large files.
  - Shared memory between processes.
- Paired with `munmap()` to release mappings.

---

### 5. Memory Locking

- **mlock() / mlockall()** – Lock memory pages into RAM to avoid swapping.
- Useful for:
  - Real-time applications.
  - Security-sensitive data (e.g., cryptographic keys).

---

### 6. Advanced Memory Techniques

- **mprotect()** – Change protection (read, write, execute) of memory regions.
- **shm_open() / shm_unlink()** – POSIX shared memory objects.
- **posix_memalign()** – Allocate memory aligned to a specified boundary.

---

### 7. Debugging Memory Issues

- Tools like **valgrind** and **AddressSanitizer** help detect:
  - Memory leaks.
  - Invalid reads/writes.
  - Use-after-free errors.
- Good practices:
  - Always initialize pointers.
  - Free resources in reverse order of allocation.

---

## Key Takeaways

- Understand the process memory layout to avoid common pitfalls.
- Use the right allocation function for your needs.
- Prefer `mmap` for large or shared allocations.
- Memory debugging tools are essential for writing reliable code.

---

## References

- *Linux System Programming, 2nd Edition* – Robert Love, O’Reilly Media.
- `man malloc`, `man mmap`, `man mprotect`, `man mlock`
