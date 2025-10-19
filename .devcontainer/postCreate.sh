#!/usr/bin/env bash
set -euo pipefail

echo "[postCreate] Running container setup..."

chmod +x .vscode/scripts/*.sh 2>/dev/null || true

git config --global --add safe.directory /workspaces/* || true
ccache --max-size=5G || true

BUILD_DIR="build"
BUILD_TYPE="${BUILD_TYPE:-Debug}"
mkdir -p "$BUILD_DIR"
cmake -S . -B "$BUILD_DIR" -G Ninja \
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
  -DCMAKE_C_COMPILER="${CC:-clang}" \
  -DCMAKE_CXX_COMPILER="${CXX:-clang++}" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON


ln -sf "${BUILD_DIR}/compile_commands.json" compile_commands.json || true
echo "[postCreate] Configured Linux build in ${BUILD_DIR} (${BUILD_TYPE})"
