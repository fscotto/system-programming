# Signal Handler

## Overview

This project demonstrates how to handle UNIX signals in C using `sigaction`.  
It specifically intercepts **SIGINT** and **SIGUSR1** and prints messages when these signals are received.

---

## Features

- Intercepts **SIGINT** (usually generated with `Ctrl + C`) and **SIGUSR1**`.
- Prints a custom message for each signal.
- Tracks the number of `SIGINT` signals received and terminates after a defined count.
- Demonstrates proper use of:
  - `sigaction()` instead of `signal()` for consistent behavior.
  - `volatile sig_atomic_t` for safe signal state handling.

---

## Build

```bash
make
```

---

## Run

```bash
./signal_handler
```

---

## Test

- Open another terminal and run:

```bash
kill -USR1 <PID>
```

where `<PID>` is the process ID of `signal_handler`.

- Press `Ctrl + C` in the terminal running the program to send `SIGINT`.

---

## Clean

```bash
make clean
```
