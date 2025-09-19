# 🛠️ Coreutils Reimplementations

This directory contains reimplementations of classic **GNU Coreutils** commands in C,  
using only **POSIX system calls** and the standard C library.

The goal is to gain hands-on experience with **Linux system programming**, while practicing  
error handling, portability, and clean coding.

---

## 📂 Structure
Each command is implemented in its own folder:
```

coreutils/
├── ls/        # list directory contents
├── cat/       # concatenate files
├── cp/        # copy files
├── echo/      # echo a string
├── sleep/     # wait X millis
````

Each subfolder contains:
- `main.c` → source code
- `Makefile` → to build the command

---

## 🎯 Learning Objectives
- Practice **file and directory operations**
- Reinforce knowledge of **system calls**: `open`, `read`, `write`, `stat`, `opendir`, `unlink`, `link`, etc.
- Develop robust error handling
- Understand the **UNIX philosophy**: small tools, combined power

---

## ⚙️ Build & Run
Example (`ls`):

```bash
cd ls
make
./ls .
````

---

*Last updated: 2025-09-18*
