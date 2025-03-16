# 🚀 Multi-Threaded Web Server  

## 📌 Description  
This project is a **multi-threaded web server** written in **C**. It follows the **producer-consumer model** to efficiently handle multiple client requests using worker threads.  
The server supports **threading, request buffering, and graceful shutdown**.

---

## ✅ Features  
✔️ Handles **multiple client requests** using threads  
✔️ Uses a **request queue (buffer)**  
✔️ Implements **mutex locks** and **condition variables**  
✔️ Supports **Ctrl + C (`SIGINT`)** for graceful shutdown  
✔️ Properly **closes all connections** when stopped  

---

## 🚀 How to Compile and Run  

### 1️⃣ Step 1: Clone the Repository  
If you haven’t already, clone this repository:  
```sh
git clone https://github.com/khanhthinh2000/multithread-webserver.git
cd multithread-webserver
```


### 2️⃣ **Step 2: Compile the Web Server**
To build the server, run:
```sh
make clean
make
```


### 3️⃣ Step 3: Run the Web Server
Use the following command to start the server:

```sh
./webserver -d www -p 8080 -t 4 -b 10
```

### Command Options:
- `-d www` → Directory for HTML files  
- `-p 8080` → Listen on port **8080**  
- `-t 4` → Use **4 worker threads**  
- `-b 10` → Buffer size of **10 requests**  


### 4️⃣ Step 4: Open in a Browser
Once the server is running, open these links in a web browser:

- `http://localhost:8080/index.html


## 🔧 How It Works  

### 1️⃣ Producer-Consumer Model  
- The **main thread (producer)** accepts client connections and adds them to a **request queue**.  
- **Worker threads (consumers)** retrieve requests from the queue and process them.  
- The web server serves the **requested HTML files** to clients.  

### 2️⃣ Thread Synchronization  
- The server uses **mutex locks** and **condition variables** to ensure **thread-safe access** to the request queue.  
- This prevents **race conditions** and **deadlocks**.  

### 3️⃣ Graceful Shutdown (`Ctrl + C`)  
- Press **`Ctrl + C`** to stop the server.  
- The server **closes all connections and cleans up worker threads** before exiting.  
- Ensures **no memory leaks and no deadlocks**.  


### 📁 Project Files  

| File | Description |
|------|------------|
| `src/webserver.c`  | Main web server code (multi-threaded implementation) |
| `src/request.c`  | Handles HTTP requests |
| `src/request.h`  | Header file for request handling |
| `Makefile`   | Used to compile the server |
| `www/index.html`  | Home page for the web server |
| `README.md`  | Project documentation |


## 👤 Author  

### 🧑‍💻 Thinh Le  
📧 Contact: [khanhthinh2000@gmail.com](mailto:khanhthinh2000@gmail.com)
