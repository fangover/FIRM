#!/usr/bin/env bash
set -euo pipefail

build_dir="${1:-build}"

if [[ -d "$build_dir" ]]; then
  rm -rf -- "$build_dir"
  echo "Removed $build_dir"
else
  echo "Nothing to clean (no $build_dir)"
fi

if [[ -L compile_commands.json ]] && readlink compile_commands.json | grep -q "$build_dir/compile_commands.json"; then
  rm -f compile_commands.json
  echo "Removed compile_commands.json symlink"
fi
