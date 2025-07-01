# 🗂️ tree – Directory Tree Viewer in C

A simplified implementation of the Unix `tree` command in C.  
This utility recursively traverses a directory and prints its structure in a tree-like format.

---

## 📦 Project Structure

```
tree/
├── main.c           # Entry point
├── tree.c           # Directory traversal logic
├── tree.h           # Function declarations
├── Makefile         # Build & test automation
└── test/
    └── run_tests.sh # Automated tests + Valgrind
```

---

## ⚙️ Build Instructions

To compile the program:

```bash
make
```

To clean up build files:

```bash
make clean
```

To remove test artifacts as well:

```bash
make distclean
```

---

## 🧪 Running Tests

The test script:

- Creates a temporary directory structure
- Runs the program and compares its output to the expected result
- Performs memory leak analysis with **Valgrind**

To run all tests:

```bash
make test
```

---

## 🚀 Usage

```bash
./tree [DIRECTORY]
```

If no directory is specified, the current directory (`.`) is used.

Example:

```bash
./tree testdir
```

Sample output:

```
|-- file1.txt
|-- sub1
  |-- file2.txt
|-- sub2
  |-- file3.txt
```

---

## 🧠 Learning Objectives

- Use of `opendir`, `readdir`, and `closedir` to iterate directories
- Handling file paths and recursion
- Working with `stat` to detect subdirectories
- Implementing simple CLI programs in C
- Using `Makefile` and Valgrind for tooling and quality

---

## ✅ Requirements

- GCC (C11)
- POSIX-compliant system (Linux, macOS)
- [Valgrind](https://valgrind.org/) for memory checking (optional, used in tests)

---

## 📄 License

Educational use only. No license required.

