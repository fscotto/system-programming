# 🧵 Chapter 7: Threads – Summary

## 📌 Key Concepts

### 🔹 What is a Thread?
- A thread is a **lightweight process** that shares the same address space (memory) with other threads of the same process.
- Threads allow concurrent execution within a single process, enabling **parallelism** and **responsiveness**.

### 🔹 Benefits of Threads
- More efficient than processes in terms of resource usage and context switching.
- Ideal for applications that perform blocking operations (e.g., I/O-bound tasks).
- Useful for **multicore scalability**.

---

## 🛠️ POSIX Threads API (pthreads)

### ➕ Creating Threads

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
````

* Spawns a new thread running `start_routine(arg)`.
* Returns a `pthread_t` handle.

### 🛑 Joining Threads

```c
int pthread_join(pthread_t thread, void **retval);
```

* Waits for the specified thread to terminate.
* Returns its return value if `retval` is not `NULL`.

### ❌ Detaching Threads

```c
int pthread_detach(pthread_t thread);
```

* Allows a thread to run independently.
* Its resources are automatically reclaimed on exit (cannot be joined).

---

## 🧩 Thread Functions

### Returning from a Thread

* Use `return` or `pthread_exit()` to terminate a thread and optionally pass back a result.

### Thread IDs

* Use `pthread_self()` to get the calling thread's ID.

---

## 🔒 Synchronization

### Mutexes

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&lock);
/* critical section */
pthread_mutex_unlock(&lock);
```

* Used to prevent **data races** in shared memory.
* Must be used carefully to avoid **deadlocks**.

### Condition Variables

```c
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_cond_wait(&cond, &mutex);
pthread_cond_signal(&cond);
```

* Used for thread coordination, e.g., waiting for a condition to become true.
* Must be used with an associated mutex.

---

## 🚧 Common Pitfalls

* Forgetting to initialize/destroy mutexes or condition variables.
* Accessing shared data without synchronization.
* Deadlocks from improper mutex locking order.
* Detached threads cannot be joined.
* Stack size: default per-thread stack may be small (configurable).

---

## 🧪 Thread Safety

* Not all C library functions are thread-safe (e.g., `strtok` is not, `strtok_r` is).
* Thread-local storage (TLS) can help isolate data per thread.

---

## 📋 Summary Table

| Function          | Purpose                           |
| ----------------- | --------------------------------- |
| `pthread_create`  | Create a thread                   |
| `pthread_join`    | Wait for a thread to finish       |
| `pthread_exit`    | End a thread                      |
| `pthread_detach`  | Run thread without joinable state |
| `pthread_mutex_*` | Locking primitives                |
| `pthread_cond_*`  | Waiting/signaling conditions      |

---

## ✅ Best Practices

* Always check return values of pthread functions.
* Protect all shared data with mutexes or atomic operations.
* Use condition variables for coordination (not busy waiting).
* Prefer modular, short-lived threads when possible.
* Clean up thread resources (`pthread_join`, `pthread_detach`).

---

*Last updated: 2025-07-28*

