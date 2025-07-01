# 📄 mycp – A Simple File Copy Utility in C

`mycp` is a basic implementation of the Unix `cp` command written in C.  
It copies the contents of one file into another, handling errors and signals safely.

---

## 📦 Project Structure

```
mycp/
├── mycp.c           # Main program source
├── Makefile         # Build and test automation
└── test/
    └── run_tests.sh # Automated test and Valgrind report
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

- Creates temporary test files
- Runs `mycp` and compares results with `cmp`
- Uses **Valgrind** to check for memory issues

Run the tests with:

```bash
make test
```

---

## 🚀 Usage

```bash
./mycp SOURCE DEST
```

- `SOURCE`: Path to the file to copy from.
- `DEST`: Path to the file to copy to.

Example:

```bash
./mycp input.txt output.txt
```

---

## 🧠 Learning Objectives

- Open/read/write/close file descriptors
- Use of `open(2)`, `read(2)`, `write(2)`, and `close(2)`
- Error handling (`perror`, `errno`)
- Use of `Makefile` and basic testing with shell scripts
- Optional: use of `lseek` for advanced length computation

---

## ✅ Requirements

- GCC (C11)
- POSIX-compliant system (Linux, macOS)
- [Valgrind](https://valgrind.org/) for memory leak analysis (optional, used in tests)

---

## 📄 License

Educational use only. No license required.

