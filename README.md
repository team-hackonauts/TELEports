# 🚀 Enhanced TELEports
**Enhanced TELEports** is a modified version of the TELEports application, designed to bring additional features and improvements to Telegram on Ubuntu Touch. This app enhances the user experience with added functionalities and optimizations while maintaining compatibility with the Ubuntu Touch ecosystem.

🛠️ **Built for FOSS Fest Winter Hackathon**  
This project was developed as part of the **FOSS Fest Winter** hackathon. We are a team of students from **REVA University, Bangalore, India**, dedicated to open-source development and improving the Ubuntu Touch ecosystem.

## ✨ Features
- 🔹 **Improved UI & Performance** – A smoother and faster experience
- 🔹 **Additional Features** – More capabilities beyond the stock TELEports app
- 🔹 **Ubuntu Touch Integration** – Seamless adaptation to the platform
- 🔹 **🔒 Secure Messaging** – Uses Telegram's API for encrypted communication

(## Still working in process on multiselect option , forward and delete option ,video recording)

## 📽️ Demo Video
[![Watch the Demo](https://img.youtube.com/vi/kD_YSsya2FQ/0.jpg)](https://youtu.be/kD_YSsya2FQ?si=cjssnk7oqI09fgR5)

## ⚙️ Prerequisites

Before installing **Enhanced TELEports**, ensure you have the required dependencies installed:

### 🖥️ Required Modules
- ✅ **C++17 compatible compiler** (Clang 5.0+, GCC 7.0+, MSVC 19.1+, Intel C++ Compiler 19+)
- ✅ **OpenSSL**
- ✅ **zlib**
- ✅ **gperf** (build only)
- ✅ **CMake (3.10+)** (build only)
- ✅ **PHP** (optional, for documentation generation)
- ✅ **Clickable** (for building & running the app)
- ✅ **Docker** (recommended for building the app)

### 🔧 Installation Steps
#### 🔹 **For Ubuntu/Linux**
Run the following commands to install the required dependencies:
```bash
sudo apt-get update
sudo apt-get install -y apt-utils
sudo apt install -y zlib1g-dev libssl-dev gperf cmake php
sudo apt install -y docker.io
sudo service docker start
```

#### 🔹 **Installing Clickable**
Clickable is required for building and running the app. Install it using `pipx`:
```bash
python3 -m pip install --user pipx
python3 -m pipx ensurepath
pipx install clickable-ut
```
If `pipx` is not installed, first install it:
```bash
sudo apt install -y python3-pip python3-venv
python3 -m pip install --user pipx
python3 -m pipx ensurepath
```

#### 🔹 **For Windows (WSL Users)**
If running on **WSL**, install `VcXsrv` and `Xlaunch` for GUI support, and enable `xhost`:
```bash
export DISPLAY=:0
xhost +
```
It is strongly recommended to run this project in an **Ubuntu environment**.

## 🏗️ Build & Run Instructions
Run the following commands to build and execute the app:

#### 🛠️ **One-time Setup for Building**
```bash
sudo su
clickable setup docker
clickable build --libs
```

#### 🚀 **Running the App (After Any Code Changes)**
```bash
clickable desktop
```

## 🛠️ Report Issues
If you encounter any issues or have suggestions, please report them here: [Report an Issue](https://reportissue.vercel.app/)

## References
1) Tdlibs Repositories
2) Teleports Repositories
