# Chapter 9 - Memory Management

This document summarizes the key concepts from **Chapter 9: Memory Management** in *Linux System Programming, 2nd Edition* by Robert Love*. It provides an overview of how memory is managed in user space, the role of the kernel, common functions for allocation and manipulation, and techniques to optimize and debug memory usage.

---

## Overview

Memory management in Linux is a fundamental component of system programming. It involves allocating, using, and releasing memory safely and efficiently. Proper memory handling avoids fragmentation, memory leaks, and undefined behavior.  

The chapter focuses on:  

- How user-space processes interact with the kernel for memory allocation.  
- The process memory layout and its components.  
- Allocation strategies in both heap and stack.  
- Advanced techniques like memory mapping and page locking.  
- Debugging tools for memory issues.

---

## Key Topics

### 1. Memory Layout of a Process

Every Linux process has a well-defined memory layout, divided into segments:

- **Text Segment** – Holds the compiled machine code of the program. Typically marked read-only and executable to prevent accidental modification.
- **Data Segment** – Contains initialized global and static variables.
- **BSS Segment** – Holds uninitialized global and static variables, which the kernel initializes to zero at program start.
- **Heap** – Dynamic memory allocated at runtime using `malloc`, `calloc`, or `realloc`. Grows upward as needed.
- **Stack** – Stores function call frames, local variables, and return addresses. Grows downward on most architectures.
- **Memory Mappings** – Regions created with `mmap()`, commonly used for shared libraries and large allocations.

> Understanding this layout is essential for writing efficient, low-level programs and debugging memory-related issues.

---

### 2. Dynamic Memory Allocation

Dynamic allocation functions allow flexible use of memory at runtime:

- **malloc(size_t size)** – Allocates a memory block of the given size without initialization.
- **calloc(size_t nmemb, size_t size)** – Allocates memory for an array of `nmemb` elements, initializing all bytes to zero.
- **realloc(void \*ptr, size_t size)** – Resizes an existing memory block, preserving its contents up to the smaller of the old and new sizes.
- **free(void \*ptr)** – Releases previously allocated memory.

#### Common pitfalls

- **Memory leaks** – Occur when allocated memory is not freed before losing all references to it.
- **Double free** – Freeing the same memory block twice, which causes undefined behavior.
- **Use-after-free** – Accessing a memory block after it has been freed, leading to crashes or data corruption.

---

### 3. `brk` and `sbrk`

Historically, `brk()` and `sbrk()` were used to manipulate the program break, which defines the end of the process’s data segment.  

- `brk()` sets the end of the data segment.
- `sbrk()` increments (or decrements) the break value.  

Modern applications rarely use these functions directly; instead, `malloc` and related functions manage them internally. These interfaces are considered low-level and non-portable.

---

### 4. Memory Mapping with `mmap`

`mmap()` maps files or anonymous memory into the process’s address space.  

#### Advantages

- Eliminates the need for additional copies when reading files.
- Enables efficient handling of large files and inter-process communication.

#### Typical use cases

- Memory-mapped file I/O.
- Shared memory regions for IPC.
- Allocating large anonymous memory regions.

To release mappings, use **munmap()**. Unlike `malloc`, which uses the heap, `mmap` provides greater flexibility for aligning memory and mapping hardware devices.

---

### 5. Advanced Memory Techniques

Several specialized APIs provide advanced control over memory:

- **mprotect()** – Changes access permissions (read, write, execute) for a memory region.
- **shm_open() / shm_unlink()** – Creates and removes POSIX shared memory objects for inter-process communication.
- **posix_memalign()** – Allocates memory aligned to a specific boundary, useful for SIMD operations or page-aligned buffers.

These functions are essential in performance-sensitive and real-time systems.

---

### 6. Debugging Memory Issues

The GNU C Library provides several functions to inspect and analyze memory usage at runtime:

- **mallinfo()**  
  Returns a `struct mallinfo` with statistics about memory allocation, such as total allocated space, number of free blocks, and fragmentation levels.
- **malloc_usable_size(void *ptr)**  
  Returns the actual usable size of an allocated block. This value may be larger than the size requested from `malloc()` due to alignment or internal overhead.
- **malloc_trim(size_t pad)**  
  Attempts to return unused memory from the heap back to the operating system, retaining `pad` bytes for future allocations. Useful for long-running processes to reduce memory footprint.
- **malloc_stats()**  
  Prints detailed statistics about memory allocation directly to `stderr`.  
  This includes information about the heap, allocated blocks, and free space.

#### Notes

- These functions are **GNU-specific** and may not be portable across different C libraries or UNIX-like systems.
- They are primarily intended for **debugging and profiling**, not for production code paths that require high performance.
- Use them to analyze fragmentation patterns, memory usage trends, and allocator behavior during development or testing.

---

### 7. Stack-Based Allocation

Stack allocation can be an efficient alternative for temporary buffers:

- **alloca(size_t size)** – Allocates memory on the calling function’s stack frame. The allocated memory is automatically released when the function returns, so `free()` is unnecessary.

#### Advantages

- Extremely fast allocation and deallocation.
- Ideal for short-lived buffers with known size limits.

#### Limitations

- Memory is valid only within the function scope. Returning a pointer to stack memory results in undefined behavior.
- Excessive allocation can lead to **stack overflow** and program crashes.
- `alloca()` is not part of the ISO C standard, but it is available as a POSIX or compiler-specific extension.

**Example**:

```c
void example(size_t size) {
    char *buffer = alloca(size);
    // Use buffer safely within this function only
}
```

---

### 8. Manipulating Memory

C provides several functions for low-level memory manipulation:

- **memset(void \*s, int c, size_t n)**  
  Fills a block of memory with a given byte value.  
  Example:

  ```c
  memset(buffer, 0, sizeof(buffer)); // Zero out buffer
  ```

- **memcpy(void \*dest, const void \*src, size_t n)**  
  Copies `n` bytes from `src` to `dest`. Behavior is undefined if regions overlap.

- **memmove(void \*dest, const void \*src, size_t n)**  
  Like `memcpy`, but handles overlapping memory correctly.

- **memcmp(const void \*s1, const void \*s2, size_t n)**  
  Compares two memory regions byte by byte, returning:
  - `< 0` if `s1` < `s2`
  - `0` if equal
  - `> 0` if `s1` > `s2`

- **memchr(const void \*s, int c, size_t n)**
  Scans the n bytes of memory pointed at by s for the character c, which is interpreted as an unsigned char

- **memmem(const void \*haystack, size_t haystacklen, const void \*needle, size_t needlelen)**
  Returns a pointer to the first occurrence of the subblock needle, of length needlelen bytes, within the block of memory haystack, of length haystacklen bytes.
  If the function does not find needle in haystack, it returns NULL.

  > This function is a GNU extension

These functions do not perform type checking or add null terminators, making them ideal for raw data operations but requiring caution to avoid buffer overruns.

---

### 9. Locking Memory

Linux provides mechanisms to lock memory pages into RAM:

- **mlock()** – Locks a specific memory range, preventing it from being swapped out.
- **mlockall()** – Locks all pages mapped by the calling process.

#### Use cases

- Real-time systems that must avoid page faults.
- Applications handling sensitive data such as encryption keys, ensuring they never hit disk.

After use, memory should be unlocked with **munlock()** or **munlockall()**.

---

## Key Takeaways

- Understanding the process memory layout is critical for writing efficient and safe programs.
- Dynamic allocation with `malloc` and its variants is powerful but requires careful management to avoid leaks and corruption.
- Use `mmap` for large or shared allocations and `alloca` for small, temporary buffers.
- Memory manipulation functions provide high performance but require strict attention to bounds and alignment.

---

## References

- *Linux System Programming, 2nd Edition* – Robert Love, O’Reilly Media.
- `man malloc`, `man mmap`, `man alloca`, `man mprotect`, `man mlock`.
