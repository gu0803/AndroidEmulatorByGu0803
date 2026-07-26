#!/usr/bin/env bash
set -euo pipefail

if ! command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1; then
  echo "x86_64-w64-mingw32-g++ was not found. Install MinGW-w64 x86_64 to build guemu.exe." >&2
  exit 1
fi

cmake -S . -B build-win64 -DCMAKE_TOOLCHAIN_FILE=cmake/mingw-w64-toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build-win64 --config Release
file build-win64/guemu.exe || true
