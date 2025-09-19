#!/usr/bin/env bash
set -euo pipefail

build_dir="${1:-build}"
target="${TARGET:-}"
jobs="${JOBS:-$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 8)}"

cmake --build "$build_dir" ${target:+--target "$target"} -j "$jobs"
