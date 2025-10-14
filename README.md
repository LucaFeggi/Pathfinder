# 🧭 A* Pathfinder

A C++ implementation of the **A*** pathfinding algorithm, visualized using **SDL2**.  

---

# 📖 Description

This project implements a visual simulation of the A* pathfinding algorithm over a circular 2D grid, rendered in real time using SDL2.
The system represents a circular path using discrete Cartesian coordinates, enabling the A* algorithm to operate as it would on a standard 2D grid while maintaining the curvature of the path. This approach facilitates extending the algorithm to handle full circuits with arbitrary shapes,
since the underlying computations are not tied to a specific coordinate system.

The implementation is modular and composed of two main components:
s
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
│   │   ├── window.hpp / window.cpp
│   │   └── input.hpp / input.cpp
│   ├── algorithm/
│   │   └── a_star.hpp / a_star.cpp
│   └── renderer/
│   	└── renderer.hpp / renderer.cpp
├── CMakeLists.txt
├── LICENCE
└── README.md
```

---

## 🔨 Build instructions

### 🪟 Windows (Visual Studio)

1. **Open a Developer Command Prompt** or use CMake GUI.  
2. **Generate project files:**
   ```bash
   cmake -B build -G "Visual Studio 17 2022"
   ```
3. **Build the project:**
   ```bash
   cmake --build build --config Release
   ```
   or open `build/Pathfinder.sln` in Visual Studio and build manually.

4. **Run the executable:**
   ```bash
   build/Release/Pathfinder.exe
   ```

> The `SDL2.dll` and `assets/` folder are automatically copied to the build directory.

---

### 🐧 Linux

1. **Generate build files:**
   ```bash
   cmake -B build
   ```
2. **Compile the project:**
   ```bash
   cmake --build build --config Release
   ```
3. **Run the executable:**
   ```bash
   ./build/Release/Pathfinder
   ```

> SDL2 headers and libraries are included under `externals/SDL2-2.32.10`, so no system installation is required.

---

## 💡 Project idea

The idea for this pathfinding implementation was inspired by an algorithmic challenge received as part of the **Race Up** assignment from **Università degli Studi di Padova**.

<img width="1086" height="1368" alt="assignment" src="https://github.com/user-attachments/assets/0e13ce34-409e-474f-b909-914abdba0333" />


---

## 🏆 Final result: shortest path found

A snapshot of the visualization after running the A* algorithm on the circular grid ($K=128$, $H=24$). The highlighted path represents the shortest Euclidean distance found from start to end points.

<img width="1709" height="1114" alt="snapshot" src="https://github.com/user-attachments/assets/4fa37a92-3652-4b34-a18a-975d6d8d60b7" />

---
