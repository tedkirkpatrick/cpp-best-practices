#!/usr/bin/env bash
# Run gcovr
set -o nounset
set -o errexit

delete=
out_def=coverage.xml
outfile=${out_def}

usage() {
  cat <<EOF
${0} [-h | --help] [-D | --delete] [--out OUT-FILE] BUILD-DIR
Collect coverage results to date into the file 'coverage.xml'.

Where
  BUILD-DIR is a CMake build directory with OPT_ENABLE_COVERAGE:BOOL=ON.

  --delete specifies that the results files (*.gcda) will be deleted after processing.
    Default is to leave the files.

  --out OUT-FILE specifies the name of the XML output file. Default: '${out_def}'.

Notes:
1. This script checks for specific clang and gcc releases. It will have to be
   extended for other releases (see case on 'cxx_ar').
EOF
}

while [[ $# -ne 0 && "$1" =~ ^- ]]; do case $1 in
  -h | --help )
    usage
    exit 1
    ;;
  -D | --delete )
    delete=--delete
    ;;
  --out )
    outfile=${2}
    shift
    ;;
  *)
    usage
    exit 1
    ;;
esac; shift; done

if [[ $# -ne 1 ]]; then
  usage
  exit 1
else
  build_dir=${1}
fi

get_cmake_cache_val() {
  # Parameters:
  # $1: -L or -LA
  # $2: Configuration parameter to search for (including type)
  val=$(cmake ${1} -N ${build_dir} | grep ${2})
  echo "${val}"
}

coverage=$(get_cmake_cache_val '-L' 'OPT_ENABLE_COVERAGE:BOOL')
if [[ "${coverage}" != 'OPT_ENABLE_COVERAGE:BOOL=ON' ]]; then
  echo "${build_dir} does not have OPT_ENABLE_COVERAGE:BOOL=ON. Found '${coverage}'"
  exit 1
fi

# Select based on 'ar' command because its file path includes compiler release
cxx_ar=$(get_cmake_cache_val '-LA' 'CMAKE_CXX_COMPILER_AR:FILEPATH')
case ${cxx_ar#CMAKE_CXX_COMPILER_AR:FILEPATH=} in
  "/usr/bin/llvm-ar-13" )
    gcov_executable="/usr/lib/llvm-13/bin/llvm-cov gcov"
    ;;
  "/usr/bin/gcc-ar-11" )
    gcov_executable="gcov-11"
    ;;
  *)
    echo "Unrecognized C++ release: '${cxx_ar}'"
    exit 1
esac

# Run this script in the build directory under test
set -o xtrace
cd ${build_dir}
gcovr ${delete} --root ../ --print-summary --xml-pretty --xml ${outfile} . --gcov-executable "${gcov_executable}"
