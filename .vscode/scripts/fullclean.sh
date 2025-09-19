#!/usr/bin/env bash
set -euo pipefail

# Directories we commonly generate
dirs=("build" "build_test" ".cache/cmake" ".cmake" "dist")
removed_any=0
for d in "${dirs[@]}"; do
  if [[ -e "$d" ]]; then
    rm -rf -- "$d"
    echo "Removed $d"
    removed_any=1
  fi
done

# Kill compile_commands.json symlink/file if present
if [[ -e compile_commands.json ]]; then
  rm -f compile_commands.json
  echo "Removed compile_commands.json"
  removed_any=1
fi

# Optional: flush ccache if CLEAR_CCACHE=1
if [[ "${CLEAR_CCACHE:-0}" == "1" ]] && command -v ccache >/dev/null 2>&1; then
  ccache -C
  echo "ccache cleared"
fi

if [[ $removed_any -eq 0 ]]; then
  echo "Nothing to clean."
fi
