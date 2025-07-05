# === Default build target using CMake ===
all:
	cmake -B build
	cmake --build build

# === Run the application ===
run: all
	./build/legacy_app

# === Run unit tests via CTest ===
test: all
	ctest --verbose --test-dir build

# === Run clang-tidy on all source files ===
tidy:
	clang-tidy main.cpp system.cpp sensor.cpp controller.cpp -- -I.

# === Clean build directory ===
clean:
	rm -rf build
