# Chapter 3 – Buffered I/O

## Difference Between Byte-Level and Buffered I/O
- **System calls** like `read()` and `write()` operate at a low level: each call may result in direct disk access.
- **C libraries** use buffered I/O (`fread()`, `fwrite()`, `fprintf()`), accumulating data in memory to reduce system calls.

## Buffered I/O API
- Uses `FILE *` type from `<stdio.h>`.
- Functions:
  - `fopen()`, `fclose()`: open/close file.
  - `fread()`, `fwrite()`: binary I/O.
  - `fprintf()`, `fscanf()`, `fgets()`, `fputs()`: formatted or text I/O.

## Types of Buffering
- **Fully buffered**: flush when buffer is full.
- **Line buffered**: flush at end of line (e.g., terminals).
- **Unbuffered**: no accumulation (e.g., stderr).

## Buffer Management
- `setvbuf()` or `setbuf()` allows custom buffering.
- Useful for optimizing performance or interactive environments.

## When to Use Buffered I/O
- When performance matters and immediate file system synchronization isn't required.
- For formatted I/O, the C library offers more simplicity and readability.

