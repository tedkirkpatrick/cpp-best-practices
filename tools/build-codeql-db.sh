#!/usr/bin/env bash
# Build database
set -o nounset
set -o errexit

config_dir_def=buildcl

usage() {
  cat <<EOF
${0} [-h | --help] [CONFIG_DIR]
Create a CodeqQL database for a C++ project built using CMake.

Where
  CONFIG_DIR is the configuration directory. Default is '${config_dir_def}'.
EOF
}

while [[ $# -ne 0 && "$1" =~ ^- ]]; do case $1 in
  -h | --help )
    usage
    exit 1
    ;;
  *)
    usage
    exit 1
    ;;
esac; shift; done

if [[ $# -gt 1 ]]; then
  usage
  exit 1
elif [[ $# -eq 1 ]]; then
  config_dir=${1}
else
   config_dir=${config_dir_def}
fi

set -o xtrace
codeql-cli/codeql database create codeql-db --language=cpp --command="cmake --build ${config_dir}"
