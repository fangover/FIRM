#!/usr/bin/env bash
set -euo pipefail

files=$(git ls-files '*.h' '*.hpp' '*.hh' '*.hxx' '*.c' '*.cc' '*.cpp' '*.cxx' 2>/dev/null || find . -type f \( -name '*.h' -o -name '*.hpp' -o -name '*.hh' -o -name '*.hxx' -o -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' \))
if [ -z "$files" ]; then
  echo "No files to format."
  exit 0
fi

clang-format -i $files
echo "Formatted $(echo $files | wc -w) files."
