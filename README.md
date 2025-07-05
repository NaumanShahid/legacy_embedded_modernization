# legacy\_embedded\_modernization

**Legacy Project Safe Modernization and Virtualized Testing of Legacy Embedded C Codebases**

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

However, this project is designed to work on **any modern Linux distribution**, including:

- Ubuntu (20.04+, recommended)
- Debian
- Arch Linux
- Fedora
- Native installations or other environments such as Docker or CI pipelines

---

## 📦 Required Tools and Dependencies

Install the following tools and dependencies using your distro's package manager:

### 🔧 System Packages (Debian/Ubuntu-based)

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

> For other distros (e.g., Fedora, Arch), use the equivalent packages via `dnf` or `pacman`.

---

### 🧪 GoogleTest Dependency (Submodule)

This project uses [GoogleTest](https://github.com/google/googletest) as a Git submodule.

After cloning the repository, run:

```bash
git submodule update --init --recursive
```

If cloning for the first time:

```bash
git clone --recurse-submodules <repo-url>
```

---

## 📁 Project Structure Overview

```
legacy_embedded_modernization/
├── src/                    # Legacy embedded codebase (.c/.cpp/.h)
├── tests/                 # GoogleTest-based unit tests
├── third_party/
│   └── googletest/        # Added as a git submodule
├── build/                 # CMake build output (gitignored)
├── .clang-format          # Code style config
├── .clang-tidy            # Linting config
├── Makefile               # Optional make wrapper
├── CMakeLists.txt         # CMake build logic
└── README.md
```

---

## ⚙️ Build Instructions

In a Linux terminal, from the project root:

### Option A: Using CMake directly

```bash
cmake -B build
cmake --build build
./build/legacy_app      # Run the application
```

### Option B: Using the provided Makefile

```bash
make         # Builds the project
make run     # Runs the built application
make tidy    # Runs clang-tidy checks
make test    # Runs unit tests
make clean   # Cleans the build
```

---

## 🥪 Running Tests

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

Run lint checks:

```bash
make tidy
```

Run code formatting manually:

```bash
clang-format -i src/*.cpp src/*.h
```

---

## 📊 Coverage & Profiling Tools

These are used during **Phase 4** of the paper:

### Code Coverage (gcov + lcov)

```bash
cmake -B build -DCMAKE_C_FLAGS="--coverage" -DCMAKE_CXX_FLAGS="--coverage"
cmake --build build
./build/legacy_app
lcov --capture --directory build --output-file coverage.info
genhtml coverage.info --output-directory coverage-report
```

Then open `coverage-report/index.html` in a browser.

### Valgrind (memory errors)

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

It's due to **clock skew** — your file timestamps appear ahead of system time.

### ✅ Fix Options:

- **WSL fix**: sync system time with:

  > Make sure `hwclock` is available by installing `util-linux-extra` first:

  ```bash
  sudo apt install util-linux-extra
  sudo hwclock -s
  ```

- **Touch files** to reset timestamps:

  ```bash
  find . -type f -exec touch {} +
  ```

- **Use native WSL directory** instead of `/mnt/e/...` to avoid NTFS timestamp quirks.

- **Force full rebuild**:

  ```bash
  make -B
  ```

---

## 💡 Tips for VSCode Integration (Optional)

- Install the [WSL Extension for VSCode](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)
- Add a `.vscode/settings.json` file:

```json
{
  "files.eol": "\n",
  "editor.formatOnSave": true,
  "C_Cpp.clang_format_path": "/usr/bin/clang-format"
}
```

---

## 🧪 Ensuring Reproducibility

Before attempting to replicate the results from the paper:

- Use a modern Linux environment (WSL or native Ubuntu recommended)
- Install all dependencies as described
- Clone the repo with `--recurse-submodules`
- Use `cmake`, `make`, `ctest`, `valgrind`, and `lcov` as shown

All static analysis, testing, and profiling results are generated in the paper using the exact setup above.

---

