# A* Pathfinder

A C++20 visualisation of the A* pathfinding algorithm on a circular grid, rendered with SDL2.

![Pathfinder visualization](https://github.com/user-attachments/assets/4fa37a92-3652-4b34-a18a-975d6d8d60b7)

## Features

- Configurable simulation parameters in `src/config.h`
- Resizable window
- Eight-direction A* pathfinding

## Controls

| Key | Action |
| --- | --- |
| `Esc` | Quit |

## Requirements

- Git
- CMake 3.25 or newer
- Ninja
- GCC and G++

On Windows 11, install a MinGW-w64 GCC toolchain and make sure `gcc`, `g++`, `cmake`,
and `ninja` are available in `PATH`.

On Ubuntu or Debian, install the tools with:

```bash
sudo apt install build-essential cmake ninja-build git
```

SDL2 is built from the `externals/SDL2` Git submodule. SDL2 may require additional
Linux development packages for the video and audio backends enabled by the system.

## Build

Clone the repository and initialize its submodule:

```bash
git clone --recurse-submodules https://github.com/LucaFeggi/Pathfinder.git
cd Pathfinder
```

If the repository was cloned without submodules, initialize them with:

```bash
git submodule update --init --recursive
```

Configure and build the debug version:

```bash
cmake --preset pathfinder-debug
cmake --build --preset pathfinder-debug --parallel
```

Configure and build the release version:

```bash
cmake --preset pathfinder-release
cmake --build --preset pathfinder-release --parallel
```

Each configuration can also be configured and built in one workflow:

```bash
cmake --workflow --preset pathfinder-debug
cmake --workflow --preset pathfinder-release
```

The `--parallel` option lets Ninja select a parallel job count based on the host
machine.

Builds are incremental. Reusing the same preset keeps the existing Ninja build
database, so unmodified sources are not rebuilt. Debug and release builds use
separate build directories.

## Run

From the repository root:

```bash
./.build/pathfinder-debug/Pathfinder
```

On Windows PowerShell:

```powershell
.\.build\pathfinder-debug\Pathfinder.exe
```

Replace `pathfinder-debug` with `pathfinder-release` to run the release build.

## Project structure

```text
Pathfinder/
├── assets/
├── externals/
│   └── SDL2/
├── src/
│   ├── app/
│   ├── renderer/
│   └── simulation/
├── CMakeLists.txt
├── CMakePresets.json
└── README.md
```
