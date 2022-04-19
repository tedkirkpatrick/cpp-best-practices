#!/usr/bin/env bash
# Run CodeQL query
set -o nounset
set -o errexit

db_def=codeql-db
db=

outfile_def=cpp-codeql-results.csv
outfile=

rerun_def=--rerun
rerun=${rerun_def}

usage() {
  cat <<EOF
${0} [-h | --help] [(-D | --database) DB_DIR] [(-O | --outfile) OUT_FILE] [-R | --no-rerun] QUERY
Run a CodeQL query against a previously-built CodeQL database. Output in CSV format.

Where
  QUERY is a path to a CodeQL query file.

  DB_DIR is a previously-build CodeQL database. Default is '${db_def}'.

  Default is to run with '${rerun_def}'. -R/--no-rerun option runs with '--no-rerun'.
EOF
}

while [[ $# -ne 0 && "$1" =~ ^- ]]; do case $1 in
  -h | --help )
    usage
    exit 1
    ;;
  -D | --database )
    db=${2}
    shift
    ;;
  -O | --outfile )
    outfile=${2}
    shift
    ;;
  -R | --no-rerun )
    rerun=
    ;;
  *)
    usage
    exit 1
    ;;
esac; shift; done

if [[ "${db}" == "" ]]; then
  db=${db_def}
fi

if [[ "${outfile}" == "" ]]; then
  outfile=${outfile_def}
fi

if [[ $# -ne 1 ]]; then
  usage
  exit 1
fi

set -o xtrace
codeql-cli/codeql database analyze --format=csv --output=${outfile} ${rerun} -- ${db} "${1}"
