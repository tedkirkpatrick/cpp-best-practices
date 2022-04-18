#!/usr/bin/env bash
# Prepend each output line with its elapsed time
# https://unix.stackexchange.com/questions/26728/prepending-a-timestamp-to-each-line-of-output-from-a-command
# Install ts in the container via 'apt-get update; apt-get -y install moreutils'
set -o nounset
set -o errexit

elapsed_format='(%H:%M:%.S)'
wall_clock_format='%Y-%m-%d %H:%M:%S'
config_dir_def=build

format=

usage() {
  cat <<EOF
${0} [-h | --help] [(-F | --format) FORMAT] [CONFIG_DIR]
Prefix each output line of 'cmake --build' with a timestamp.

Where
  FORMAT is one of
     elapsed     display elapsed time
     wall_clock  display wall clock time
     both        display wallk clock and elapsed time
  Default is 'elapsed'.

  CONFIG_DIR is the configuration directory. Default is '${config_dir_def}'.
EOF
}

get_format() {
  case $1 in
    elapsed )
      echo ${elapsed_format}
      ;;
    wall_clock )
      echo ${wall_clock_format}
      ;;
    both )
      echo "[${wall_clock_format} ${elapsed_format}]"
      ;;
    *)
      echo "BAD_FORMAT"
      ;;
  esac
}

while [[ $# -ne 0 && "$1" =~ ^- ]]; do case $1 in
  -h | --help )
    usage
    exit 1
    ;;
  -F | --format )
    format=$(get_format "$2")
    if [[ ${format} == BAD_FORMAT ]]; then
      usage
      exit 1
    fi
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
  config_dir=${1}
else
   config_dir=${config_dir_def}
fi

if [[ ${format} == "" ]]; then
  format=${elapsed_format}
fi

set -o xtrace
cmake --build ${config_dir} | ts -s "${format}"
