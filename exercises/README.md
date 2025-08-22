# 🗂️ Exercise Index – Linux System Programming

This is an organized list of all exercises completed so far, including a brief description and links to related resources or files.

---

## 📁 mycp

**Description**: A simple file copy utility implemented in C using low-level system calls (`open`, `read`, `write`, `close`).

- 📄 [README](mycp/README.md)
- 📂 Directory: `mycp/`
- ✅ Features:
  - Error handling via `perror` and `errno`
  - Safe loop with `EINTR` handling
  - Proper resource cleanup
  - Integrated unit tests and Valgrind checks

---

## 🌳 tree

**Description**: A basic reimplementation of the Unix `tree` utility that recursively lists directories and files.

- 📄 [README](tree/README.md)
- 📂 Directory: `tree/`
- ✅ Features:
  - Recursive traversal using `opendir` and `readdir`
  - Directory depth display
  - Unit tests with mocks for directory structure
  - Scripted test automation with Valgrind integration

---

## 🐚 run_scripts

**Description**: A simple C program that sequentially executes one or more bash scripts, printing each script’s exit status.

- 📄 [README](run_scripts/README.md)
- 📂 Directory: `run_scripts/`
- ✅ Features:
  - Uses `fork()` and `execlp()` to run each script in a child process
  - Waits for each child to finish before executing the next
  - Reports normal exit code or termination by signal
  - Includes example test scripts and memory checks with Valgrind
  - Makefile with targets: `build`, `run`, `test`, `valgrind`, and `clean`

---

## 📥 downloader

**Description**: A multi-threaded simulated file downloader implemented in C using POSIX threads (pthreads).

- 📄 [README](downloader/README.md)
- 📂 Directory: `downloader/`
- ✅ Features:
  - Each thread simulates downloading a file by printing periodic progress updates
  - Synchronization using `pthread` APIs
  - Demonstrates creation, execution, and joining of threads
  - Makefile included with standard targets

---

## 🧠 memory_analyzer

**Description**: A simple memory analyzer that allocates memory blocks of different sizes and prints current memory usage.

- 📄 [README](mem_analyzer/README.md)
- 📂 Directory: `mem_analyzer/`
- ✅ Features:
  - Allocates blocks using `malloc` and frees them after measurement
  - Reports current memory usage via `/proc/self/status`
  - Minimal implementation aligned with the exercise objectives
  - Makefile included with standard targets

---

## 🚦 signal_handler

**Description**: A C program demonstrating robust signal handling for `SIGINT` and `SIGUSR1` using `sigaction` with `SA_SIGINFO`.

- 📄 [README](signal_handler/README.md)
- 📂 Directory: `signal_handler/`
- ✅ Features:
  - Handles `SIGINT` up to three times before exiting
  - Handles `SIGUSR1` with a simple message
  - Masks signals during handler execution to avoid reentrancy issues
  - Includes comments and clear separation of handler logic
  - Makefile included with standard targets

---

## 🔧 Tooling & Automation

**Shared tools and scripts used across projects**:

- `Makefile` with:
  - Targets for `build`, `test`, `valgrind`, and `clean`
- Shell script for automated tests: `run_tests.sh`
- Valgrind memory check reports generated automatically
