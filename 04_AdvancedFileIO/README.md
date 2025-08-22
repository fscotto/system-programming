# Chapter 4 – Advanced File I/O

## Scatter/Gather I/O
- Scatter/gather I/O allows reading or writing data to/from multiple buffers in a single system call.
- Uses `readv()` and `writev()`:
  - `readv(fd, iov, iovcnt)`: reads into multiple buffers (`iov` array).
  - `writev(fd, iov, iovcnt)`: writes from multiple buffers.
- Improves efficiency by reducing system calls.

## Event Poll (`select()`, `poll()`, `epoll`)
- Traditional multiplexing: `select()`, `poll()` (limited scalability).
- Linux-specific: `epoll` for efficient event notification.
  - `epoll_create()`: create epoll instance.
  - `epoll_ctl()`: control interest list (add, modify, remove fds).
  - `epoll_wait()`: wait for events.
- Edge-triggered vs level-triggered modes.

## Memory-Mapped Files (`mmap()`)
- Maps files or devices into memory for direct access.
- System calls: `mmap()`, `munmap()`.
- Benefits: faster I/O, shared memory.
- Use `msync()` to synchronize changes.
- Resizing mappings, changing protections.
- Advisory calls:
  - `posix_fadvise()`: give advice about expected I/O patterns.
  - `readahead()`: prefetch file data.
- Pros and cons of memory mapping.

## Asynchronous I/O and I/O Scheduling
- Distinction between synchronous and asynchronous I/O.
- Linux AIO APIs for asynchronous operations.
- I/O schedulers:
  - Manage disk request ordering.
  - Examples: CFQ, noop, deadline.
- Optimizing I/O performance by choosing schedulers.
- Concepts of disk addressing and request life cycle.

## Miscellaneous
- `ioctl()`: device-specific operations.
- Zero-copy transfers: `sendfile()`, `splice()`.

---

> This chapter covers advanced Linux I/O techniques aimed at improving performance and flexibility in system programming.

