# legacy_embedded_modernization

**Legacy Project: Safe Modernization and Virtualized Testing of Legacy Embedded C Codebases**

---

## 🛠️ Environment Setup Guide (Reproducibility Checklist)

This project has been tested and verified in the following environment:

- **Author's Setup**:
  - **Host OS**: Windows 10/11 (x64)
  - **Linux Distro**: Ubuntu 24.04.2 LTS via WSL2
  - **Code Editor**: [Visual Studio Code](https://code.visualstudio.com/) (Windows version, accessed via WSL integration)
  - **Shell**: Bash
  - **Git settings**:
    ```bash
    git config --global core.autocrlf input
    git config --global core.eol lf
    ```

> ✅ This project is also compatible with native Linux (Ubuntu, Debian, Arch, Fedora, etc.) or inside containers (e.g., Docker).

---

## 📦 Required Tools and Dependencies

Install the following packages:

### Debian/Ubuntu:

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  cmake \
  clang \
  clang-tidy \
  clang-format \
  valgrind \
  lcov \
  git \
  gdb \
  gcovr \
  curl \
  unzip \
  util-linux-extra  # Required for hwclock (especially in WSL)
```

> 🔧 On other distros, use equivalent packages via `dnf`, `pacman`, etc.

---

## 🧪 GoogleTest Dependency (Submodule)

This project uses [GoogleTest](https://github.com/google/googletest) as a submodule.

If you've already cloned the repo:

```bash
git submodule update --init --recursive
```

Or when cloning for the first time:

```bash
git clone --recurse-submodules <repo-url>
```

---

## 📁 Project Structure

```
legacy_embedded_modernization/
├── src/                    # Legacy embedded code (.c/.cpp/.h)
├── tests/                 # GoogleTest unit tests
├── third_party/
│   └── googletest/        # Git submodule
├── build/                 # CMake build output (gitignored)
├── .clang-format          # Code style config
├── .clang-tidy            # Linting config
├── Makefile               # Optional make wrapper
├── CMakeLists.txt         # Build logic
├── fix_clock_skew.sh      # Optional: Clock skew fixer
└── README.md              # This file
```

---

## ⚙️ Build Instructions

### Option A: Using CMake

```bash
cmake -B build
cmake --build build
./build/legacy_app
```

### Option B: Using Make

```bash
make         # Build the project
make run     # Run the binary
make tidy    # Run clang-tidy checks
make test    # Run unit tests
make clean   # Clean build
```

---

## 🧪 Running Unit Tests

```bash
cd build
ctest --output-on-failure
```

Or simply:

```bash
make test
```

---

## 🧼 Linting & Formatting

Run lint:

```bash
make tidy
```

Format code manually:

```bash
clang-format -i src/*.cpp src/*.h
```

---

## 📊 Code Coverage & Profiling

Used in **Phase 4** of the research.

### Code Coverage (gcov + lcov)

```bash
cmake -B build -DCMAKE_C_FLAGS="--coverage" -DCMAKE_CXX_FLAGS="--coverage"
cmake --build build
./build/legacy_app
lcov --capture --directory build --output-file coverage.info
genhtml coverage.info --output-directory coverage-report
```

Open `coverage-report/index.html` in a browser.

### Valgrind (memory leak checks)

```bash
valgrind --leak-check=full ./build/legacy_app
```

### gprof (CPU profiling)

```bash
cmake -B build -DCMAKE_C_FLAGS="-pg" -DCMAKE_CXX_FLAGS="-pg"
cmake --build build
./build/legacy_app
gprof ./build/legacy_app gmon.out > gprof-report.txt
```

---

## 🧭 Clock Skew Issues (WSL or Dual Boot Users)

If you see build warnings like:

```
gmake: Warning: File 'Makefile' has modification time in the future
```

It’s caused by **clock skew** — timestamps are ahead of system time.

### ✅ How to Fix

1. Sync your system time:

   ```bash
   sudo apt install util-linux-extra      # If not already installed
   sudo hwclock -s
   ```

2. Run the helper script to touch all files:

   ```bash
   ./fix_clock_skew.sh
   ```

   (If not present, run manually: `find . -type f -exec touch {} +`)

3. Rebuild your project:

   ```bash
   make clean && make
   ```

4. Avoid working inside `/mnt/c/...` or other NTFS mount paths in WSL for best file system consistency.

---

## 💡 VSCode Integration (Optional)

Install the [WSL Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl) for VSCode.

Example `.vscode/settings.json`:

```json
{
  "files.eol": "\n",
  "editor.formatOnSave": true,
  "C_Cpp.clang_format_path": "/usr/bin/clang-format"
}
```

---

## 📌 Reproducibility Summary

To replicate this project:

- Use any modern Linux system (Ubuntu recommended)
- Clone with submodules
- Install dependencies
- Run: `cmake -B build && cmake --build build`
- Run: `make tidy`, `make test`, `valgrind`, `lcov`, `gprof`
- If on WSL, run `sudo hwclock -s && ./fix_clock_skew.sh` to prevent build errors

All experiments in the paper were generated using these steps and this environment.

---
