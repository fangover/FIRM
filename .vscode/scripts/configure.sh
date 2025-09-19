set -euo pipefail

build_dir="${1:-build}"
build_type="${BUILD_TYPE:-Debug}"

mkdir -p "$build_dir"

cmake -S . -B "$build_dir" -G Ninja \
  -DCMAKE_BUILD_TYPE="$build_type" \
  -DCMAKE_C_COMPILER="${CC:-clang}" \
  -DCMAKE_CXX_COMPILER="${CXX:-clang++}" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

ln -sf "${build_dir}/compile_commands.json" compile_commands.json || true

echo "Configured Linux build in ${build_dir} (${build_type})"
