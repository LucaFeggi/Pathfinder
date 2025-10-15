# 🧭 A* pathfinder

A C++ implementation of the **A*** pathfinding algorithm, visualized using **SDL2**.  

---

# 📖 Description

This project implements a visual simulation of the A* pathfinding algorithm over a circular 2D grid, rendered in real time using SDL2.
The system represents a circular path using discrete Cartesian coordinates, enabling the A* algorithm to operate as it would on a standard 2D grid while maintaining the curvature of the path. This approach facilitates extending the algorithm to handle full circuits with arbitrary shapes,
since the underlying computations are not tied to a specific coordinate system.

---

## 🚀 Features

- Fully configurable parameters via `config.hpp`  
- Resizeable window

---


## 🎮 Controls

| Key | Action |
|-----|---------|
| `Esc`| Quit the simulation |

---

## ⚙️ Project structure

```
Pathfinder
│
├── src/
│   ├── config.hpp
│   ├── main.cpp
│   ├── app/	
│   │   ├── app.hpp / app.cpp
│   │   ├── input.hpp / input.cpp
│   │   └── window.hpp / window.cpp
│   ├── simulation/
│   │   └── a_star.hpp / a_star.cpp
│   └── renderer/
│   	  └── renderer.hpp / renderer.cpp
├── assets/
│   └── icon/
│       └── icon.bmp
├── externals/
│   └── SDL2-2.32.10/
├── CMakeLists.txt
├── README.md
└── LICENCE
```

---

## 🔨 Build Instructions

## 🪟 Windows (Visual Studio)

> 📝 **Notes:**
> - **SDL2** is automatically setupped ── no installation needed.

1. **Open cmd**
2. **Clone this repository:**
   ```bash
   git clone https://github.com/LucaFeggi/Pathfinder
   ```
3. **Enter the project root:**
   ```bash
   cd Pathfinder
   ```
4. **Generate project files:**
   ```bash
   cmake -B build -G "Visual Studio 17 2022"
   ```
5. **Build the project:**
   ```bash
   cmake --build build --config Release
   ```

6. **Run the executable:**
   ```bash
   build\Release\Pathfinder.exe
   ```

## 🐧 Linux (Ubuntu/Debian)

> 📝 **Notes:**
> - **SDL2** must be installed on the system, if not already present.
> - Make sure you’re running under the **X11 display server** (not Wayland), as SDL2 currently requires it.

1. **Open cmd**
2. **Download SDL2 (optional):**
   ```bash
   sudo apt install libsdl2-dev
   ```
3. **Clone this repository:**
   ```bash
   git clone https://github.com/LucaFeggi/Pathfinder
   ```
4. **Enter the project root:**
   ```bash
   cd Pathfinder
   ```
5. **Generate build files:**
   ```bash
   cmake -B build
   ```
6. **Compile the project:**
   ```bash
   cmake --build build --config Release
   ```
7. **Run the executable:**
   ```bash
   ./build/Pathfinder
   ```

---


## 💡 Project idea

The idea for this pathfinding implementation was inspired by an algorithmic challenge received as part of the **Race Up** assignment from **Università degli Studi di Padova**.

<img width="1086" height="1368" alt="assignment" src="https://github.com/user-attachments/assets/0e13ce34-409e-474f-b909-914abdba0333" />


---

## 🏆 Final result: shortest path found

A snapshot of the visualization after running the A* algorithm on a semicircular grid ($K=128$, $H=24$). The highlighted path represents the shortest Euclidean distance found from start to end point.

<img width="1709" height="1114" alt="snapshot" src="https://github.com/user-attachments/assets/4fa37a92-3652-4b34-a18a-975d6d8d60b7" />

---
