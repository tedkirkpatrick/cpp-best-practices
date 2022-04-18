#!/usr/bin/env bash
# Run a sample CodeQL query on the pre-built database
set -o nounset
set -o errexit

codeql_query_dir_def='/home/cpp_best/codeql/cpp/ql/src/Best Practices'
codeql_query_dir=${codeql_query_dir_def}

query_def=RuleOfThree.ql

usage() {
  cat <<EOF
${0} [-h | --help] [(-D | --directory) DIR] [QUERY]
Run a CodeqQL query for this test project.

Where
  QUERY is the query to run, including '.ql' suffix. Default '${query_def}'.
  DIR is path to the directory containing the query. Default '${codeql_query_dir_def}'.
EOF
}

while [[ $# -ne 0 && "$1" =~ ^- ]]; do case $1 in
  -h | --help )
    usage
    exit 1
    ;;
  -D | --directory )
    codeql_query_dir=${2}
    shift
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
  query=${1}
else
  query=${query_def}
fi

if [[ ! -d codeql-test ]]; then
  echo "Run this script from the parent directory."
  exit 1
fi

set -o xtrace
tools/codeql-query.sh -D codeql-test/codeql-test-db/ "${codeql_query_dir}/${query}"
