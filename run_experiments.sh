#!/bin/bash

set -e

echo ">> Cleaning previous build..."
rm -rf build gmon.out coverage.info coverage-report valgrind-report.txt gprof-report.txt

echo ">> Configuring with coverage and profiling flags..."
cmake -B build -DCMAKE_C_FLAGS="--coverage -pg" -DCMAKE_CXX_FLAGS="--coverage -pg"

echo ">> Building project..."
cmake --build build

echo ">> Running application..."
./build/legacy_app

echo ">> Running gprof..."
gprof ./build/legacy_app gmon.out > gprof-report.txt

echo ">> Running lcov coverage..."
lcov --capture --directory build --output-file coverage.info
genhtml coverage.info --output-directory coverage-report

echo ">> Running valgrind..."
valgrind --leak-check=full ./build/legacy_app > valgrind-report.txt 2>&1

echo ">> All reports generated:"
echo "   - gprof-report.txt"
echo "   - valgrind-report.txt"
echo "   - coverage-report/index.html"
