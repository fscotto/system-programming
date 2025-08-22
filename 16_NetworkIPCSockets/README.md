# 📘 APUE – Chapter 16: Sockets Summary

### **1. Introduction to Sockets**

- Sockets are an abstraction for network communication.
- Enable communication between processes over the network.
- Support multiple protocols: TCP, UDP (IPv4, IPv6).

### **2. Socket Types**

- `SOCK_STREAM` – TCP (reliable, connection-oriented).
- `SOCK_DGRAM` – UDP (connectionless, unreliable).
- `SOCK_SEQPACKET` – sequenced, reliable datagrams (less common).
- `SOCK_RAW` – raw access to IP packets (used in advanced networking).

### **3. Socket System Calls**

1. `int socket(int domain, int type, int protocol);`
   - Create a new socket descriptor.
2. `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
   - Assign an address/port to a socket (server side).
3. `int listen(int sockfd, int backlog);`
   - Mark socket as passive (ready to accept connections).
4. `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`
   - Accept a new incoming connection (blocking call).
5. `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
   - Establish connection to a server (client side).
6. `ssize_t read(int sockfd, void *buf, size_t count);`
7. `ssize_t write(int sockfd, const void *buf, size_t count);`
8. `ssize_t recv(int sockfd, void *buf, size_t len, int flags);`
9. `ssize_t send(int sockfd, const void *buf, size_t len, int flags);`
10. `int close(int sockfd);`
    - Close the socket and free resources.

### **4. Socket Address Structures**

- IPv4: `struct sockaddr_in`

  ```c
  struct sockaddr_in {
      sa_family_t sin_family;  // AF_INET
      in_port_t sin_port;      // port number (network byte order)
      struct in_addr sin_addr; // IP address
  };
  ```

- IPv6: `struct sockaddr_in6`
- Generic: `struct sockaddr` for compatibility.

### **5. Data Conversion Utilities**

- `htons()`, `htonl()`: host to network byte order (short/long)
- `ntohs()`, `ntohl()`: network to host byte order
- `inet_pton()`: convert string IP to `struct in_addr` or `struct in6_addr`
- `inet_ntop()`: convert address structure to string

### **6. TCP Client-Server Model**

**Server:**

1. `socket()`
2. `bind()`
3. `listen()`
4. `accept()` → handle client
5. `read()/write()` → communicate
6. `close()`

**Client:**

1. `socket()`
2. `connect()`
3. `read()/write()` → communicate
4. `close()`

### **7. UDP Model**

- Connectionless: no `listen()`/`accept()`.
- Use `sendto()` and `recvfrom()` for communication.
- No guarantee of delivery; suitable for lightweight or real-time protocols.

### **8. Concurrency in Servers**

- **Process-based**: `fork()` for each client
- **Thread-based**: `pthread_create()` for each client
- **I/O multiplexing**: `select()`, `poll()`, `epoll()`

### **9. Error Handling**

- Check return values of all socket calls.
- Use `perror()` or `strerror()` for diagnostics.
- Handle `EINTR` for interruptible syscalls.

### **10. Key Takeaways**

- Sockets abstract network communication using familiar file descriptor semantics.
- TCP ensures reliable, ordered delivery; UDP is fast but unreliable.
- Address conversions (`inet_pton`, `inet_ntop`) are essential for portability.
- Concurrency requires careful design: processes, threads, or event loops.
- Practice writing small client-server programs to solidify concepts.
