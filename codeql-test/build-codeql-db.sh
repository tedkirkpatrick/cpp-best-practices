#!/usr/bin/env bash
# Build database
set -o nounset
set -o errexit

CODEQL_HOME=../codeql-cli

usage() {
  cat <<EOF
${0} [-h | --help]
Create a CodeqQL database for this test project.
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

if [[ $# -gt 0 ]]; then
  usage
  exit 1
fi

if [[ ! -d codeql-test ]]; then
  echo "Run this script from the parent directory."
  exit 1
fi

set -o xtrace
cd codeql-test && \
${CODEQL_HOME}/codeql database create codeql-test-db --overwrite --language=cpp --command="make --always-make"
