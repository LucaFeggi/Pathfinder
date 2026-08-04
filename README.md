# A* Pathfinder

A C++20 visualisation of the A* pathfinding algorithm on a circular grid, rendered with SDL2.

![Pathfinder visualization](https://github.com/user-attachments/assets/4fa37a92-3652-4b34-a18a-975d6d8d60b7)

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

Each configuration can also be configured and built in one workflow:

```bash
cmake --workflow --preset pathfinder-debug
cmake --workflow --preset pathfinder-release
```

Ninja selects the parallel job count automatically based on the host machine.

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
