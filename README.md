# KronosDB: A High-Performance C++ Key-Value Store

KronosDB is a persistent, high-performance, and concurrent key-value database server built from the ground up in C++.
Inspired by systems like Redis, this project demonstrates modern C++ techniques for asynchronous networking, advanced concurrency control, and durable data storage.

---

## Core Features

* **Asynchronous Network I/O:** Built with **Boost.Asio** to manage a large number of simultaneous client connections efficiently without blocking.
* **High-Concurrency with Lock Striping:** Engineered a thread-safe data core using a fine-grained **lock striping** strategy with a pool of `std::shared_mutex` objects. This significantly reduces thread contention and enables high-throughput parallel writes.
* **Durable Data Persistence:** Implements an **Append-Only File (AOF)** mechanism. Every write operation (`SET`, `DEL`) is logged to disk, ensuring data integrity and fault tolerance across server restarts.
* **Containerized & Portable:** Fully containerized with a multi-stage **Dockerfile**, providing a lightweight, portable, and isolated environment for easy deployment. The official image is available on Docker Hub.
* **Modern C++:** Written using modern C++17 features, including smart pointers (`std::shared_ptr`, `std::unique_ptr`), `std::optional`, and standard library threading primitives for robust and safe resource management.

---

## Technology Stack

| Component            | Technology |
| -------------------- | ---------- |
| **Language**         | C++17      |
| **Networking**       | Boost.Asio |
| **Build System**     | CMake      |
| **Containerization** | Docker     |

---

## Getting Started with Docker (Recommended)

The easiest way to get KronosDB running is by using the pre-built Docker image available on Docker Hub.

**Run the container:**

```bash
docker run -d -p 12345:12345 --name kronosdb anshbalar429/kronosdb:latest
```

Your KronosDB instance is now running.

---

## Interacting with KronosDB

> **Note:** You can connect to the server using any raw TCP client.
> **Connection Details:**
>
> * **Host:** `localhost`
> * **Port:** `12345`

### 1. Using the `kronos-cli`

```bash
docker exec -it kronosdb ./build/kronos-cli
```

### 2. Using `netcat`

Run this in your local terminal:

```bash
nc localhost 12345
```

---

## Protocol Commands

| Command             | Description       | Response         |
| ------------------- | ----------------- | ---------------- |
| `SET <key> <value>` | Stores a value    | `OK`             |
| `GET <key>`         | Retrieves a value | Value or `(nil)` |
| `DEL <key>`         | Deletes a key     | `OK`             |

**Example Session:**

```
$ nc localhost 12345
SET name Kronos
OK
GET name
Kronos
GET location
(nil)
DEL name
OK
GET name
(nil)
```

---

### 3. Using the Python Client

For programmatic access, you can use a simple client like this:

```python
# client.py
import socket

def send_command(command_string):
    """Sends a command to the server and returns the response."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(('localhost', 12345))
        s.sendall((command_string + '\n').encode('utf-8'))
        response = s.recv(1024)
        return response.decode('utf-8').strip()

# Example usage:
print(f"Server response: {send_command('SET city Prague')}")
print(f"Server response: {send_command('GET city')}")
```

---

## Building from Source

If you prefer to build the project yourself:

### Prerequisites

* A C++17 compatible compiler (e.g., GCC 9+, Clang 7+)
* CMake (3.16+)
* Boost Libraries (System, Thread)

### Build Steps

```bash
# 1. Clone the repository
git clone https://github.com/AnshBalar429/KronosDB.git
cd KronosDB

# 2. Configure the project with CMake
cmake -B build

# 3. Compile the project
cmake --build build

# 4. Run the server
./build/KronosDB
```

---

## Architecture Overview

The server is designed with a clean separation of concerns:

* **`Server`** – Accepts incoming TCP connections using Boost.Asio.
* **`Session`** – Manages the lifecycle of a single client connection, handling asynchronous reading, command parsing, and writing responses.
* **`KeyValueStore`** – The thread-safe data core holding the in-memory `std::unordered_map` and implementing high-performance lock striping logic.
* **`Persistence`** – Handles all file I/O for the Append-Only File (AOF), ensuring data durability.

---
