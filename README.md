# 🚀 TCP/IP Handshake Communication Project

## 📌 Overview

This project demonstrates a **TCP client-server communication system** implemented in **C++ (Winsock)**.
It simulates a simplified version of the **TCP 3-way handshake** and supports **continuous data transmission with timestamps**.

---

## 🧠 Key Concepts Covered

* TCP Socket Programming (Client-Server)
* 3-Way Handshake (SYN → SYN-ACK → ACK)
* Continuous Data Streaming
* Timestamp Logging
* Windows Networking using Winsock

---

## 🔄 Handshake Flow

Client and Server establish connection using:

```
Client → Server : SYN  
Server → Client : SYN-ACK  
Client → Server : ACK  
```

After successful handshake → data transmission begins.

---

## 🏗️ Architecture

```
Client                          Server
  | -------- SYN ---------->      |
  | <------ SYN-ACK --------      |
  | -------- ACK ---------->      |
  | ===== DATA STREAM =====       |
```

---

## ⚙️ Features

✅ Custom TCP handshake implementation
✅ Continuous data transfer (real-time simulation)
✅ Timestamp added to each message
✅ Error handling using Winsock
✅ Cross-platform extendable (Windows → Linux/QNX)

---

## 📦 Project Structure

```
tcp_ip_protocol_handshake/
│
├── client.cpp
├── server.cpp
├── Makefile
├── README.md
```

---

## 🛠️ Requirements

* Windows OS
* MinGW / MSYS2
* g++ compiler
* Git (optional)

---

## ⚙️ Build Instructions

```bash
mingw32-make
```

---

## ▶️ Run Instructions

### Start Server

```bash
server.exe
```

### Start Client

```bash
client.exe
```

---

## 📊 Sample Output

### Client

```
Sent: DATA:45 | TIME:2026-04-18 19:10:01
Sent: DATA:78 | TIME:2026-04-18 19:10:02
```

### Server

```
Received: DATA:45 | TIME:2026-04-18 19:10:01 | SERVER_TIME:2026-04-18 19:10:01
Received: DATA:78 | TIME:2026-04-18 19:10:02 | SERVER_TIME:2026-04-18 19:10:02
```

---

## 🔥 Future Enhancements

* 🔄 Multi-client support (threaded server)
* ⏱️ Latency measurement (RTT calculation)
* 📁 Logging to file (CSV/JSON)
* 🔐 Secure communication (TLS/SSL)
* 🌐 Cross-platform support (Linux, QNX)

---

## 🎯 Use Cases

* Embedded systems communication (QNX, ADAS)
* Telemetry / sensor data streaming
* Network protocol learning
* Client-server architecture demos

---

## 👨‍💻 Author

**Gaurav Sharma**
GitHub: https://github.com/gauravsharmagrv26

---

## ⭐ If you like this project

Give it a ⭐ on GitHub and feel free to contribute!
