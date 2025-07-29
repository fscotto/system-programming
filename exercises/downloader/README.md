# 🧵 Multi-threaded File Downloader (Simulated)

This project simulates a multi-threaded file downloader in C using POSIX threads (`pthreads`). The goal is to practice creating and managing threads, synchronizing access to shared resources, and simulating parallel file downloads.

---

## 📋 Description

Each file provided via command-line arguments is "downloaded" by a separate thread. The download is simulated by printing log messages and sleeping for a random duration. All threads run concurrently and the main thread waits for them to complete.

This project is inspired by Chapter 7 ("Threads") of *Linux System Programming* by Robert Love.

---

## 🚀 Usage

```bash
$ ./downloader file1.txt file2.txt file3.txt
````

Each file will be "downloaded" in parallel by a separate thread. The program prints informative messages about the start and completion of each download.

---

## 🛠️ Features

* One thread per file
* Simulated download using `sleep()`
* Optional logging to file (future enhancement)
* Thread-safe output via `pthread_mutex_t`
* Clean thread termination via `pthread_join`

---

## 🧪 Example Output

```
[Thread 0x7fdc9a10]: Starting download of file1.txt
[Thread 0x7fdc9210]: Starting download of file2.txt
[Thread 0x7fdc9210]: Finished download of file2.txt
[Thread 0x7fdc9a10]: Finished download of file1.txt
All downloads complete.
```

---

## 📂 Project Structure

```
multidownload/
├── main.c         # Main program
├── Makefile       # Build script
└── README.md      # Project documentation
```

---

## 🧵 Concepts Practiced

* Thread creation with `pthread_create`
* Thread joining with `pthread_join`
* Synchronization with `pthread_mutex_t`
* Struct-based thread argument passing
* Output race condition prevention

---

## 🏗️ Build

```bash
$ make
```

To clean the build:

```bash
$ make clean
```

---

## 📖 References

* *Linux System Programming* by Robert Love — Chapter 7: Threads
* POSIX Threads (man 7 pthread)

---

*Last updated: 2025-07-28*
