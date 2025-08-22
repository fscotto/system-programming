# Chapter 2 – File I/O

## Basic Concepts
- File I/O is central in Linux: every entity (file, socket, device) is treated as a file.
- The kernel manages a **file table** per process, with descriptors and metadata like offset and mode.

## Core Operations
1. **`open()`**:
   - Opens a file with flags (O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_SYNC, O_DIRECT).
   - Returns a file descriptor or -1 on error.
   - Sets owner and permissions for newly created files.
2. **`read()` / `write()`**:
   - `read(fd, buf, n)` reads up to **n** bytes, returns bytes read or -1.
   - `write(fd, buf, n)` writes, handles partial writes, append mode and non-blocking I/O.
   - Common errors: EAGAIN, EINTR, ECC.
3. **I/O Synchronization**:
   - `fsync()` and `fdatasync()` flush to disk.
   - `O_SYNC`, `O_DSYNC`, `O_RSYNC` for open-time synchronization.
   - `sync()` syncs all files to disk.
4. **`lseek()`**:
   - Moves the **offset** within the file—can be positive/negative; allows sparse writes.
5. **`close()`**:
   - Frees the descriptor. Returns 0 or -1 on error.

## Positional I/O
- `pread()` / `pwrite()` allow read/write at specific offsets without altering the shared file offset (useful in multithreaded environments).

## Multiplexed I/O
- Functions like `select()` and `poll()` manage multiple file descriptors for asynchronous I/O.
- More scalable option: `epoll()` (covered in Chapter 4).
