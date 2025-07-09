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

## 🔧 Tooling & Automation

**Shared tools and scripts used across projects**:

- `Makefile` with:
  - Targets for `build`, `test`, `valgrind`, and `clean`
- Shell script for automated tests: `run_tests.sh`
- Valgrind memory check reports generated automatically

*Last updated: 2025-07-09*
