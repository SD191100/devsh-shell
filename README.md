# 🚀 Custom Shell in C++

A lightweight, minimalistic shell built in **C++** that mimics basic Unix shell behavior. This shell supports **built-in commands**, **path resolution**, and **external command execution**.

## 🔹 Features
✔️ Basic shell prompt with user info  
✔️ Built-in commands: `echo`, `exit`, `type`  
✔️ Execute system commands like `ls`, `pwd`, `cat`  
✔️ Custom **path resolution** using `$PATH`  
✔️ Handles **single (' ') and double (" ") quotes** correctly  
✔️ Supports **whitespace-separated arguments**  

---

## 📌 How It Works

### 🛠 Built-in Commands
| Command           | Description                                      |
|------------------|--------------------------------------------------|
| `echo "Hello"`   | Prints `Hello` to the console                    |
| `exit`          | Exits the shell                                   |
| `type command`  | Checks if a command is built-in or external       |

### 💻 Running System Commands
You can execute **any system command** available in `$PATH`:
```sh
ls -l
pwd
cat file.txt
```
## 📦 Installation & Usage

### 🛠 Prerequisites
Ensure you have:
- **g++ (GCC Compiler)**
- **Linux/macOS terminal** (Windows users can use WSL)

### ⚡ Installation Steps

1️⃣ **Clone the repository**  
```sh
git clone https://github.com/your-username/custom-shell.git
cd custom-shell
```

2️⃣ **Compile the shell**  
```sh
g++ shell.cpp -o mysh -std=c++17 -lstdc++fs
```

3️⃣ **Run the shell**  
```sh
./mysh
```

Now, you're inside your **custom shell!** 🎉  
```sh
tanjiro % echo "Hello, World!"
Hello, World!
```

