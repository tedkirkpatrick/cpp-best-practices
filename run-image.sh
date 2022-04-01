#!/usr/bin/env bash
# Run the cpp-best-practices dev environment as a container
set -o nounset
set -o errexit

image_name=cpp_best
image_ver=2022.4

TZ=${TZ:-Canada/Pacific}

container_dir=/home/cpp_best

usage() {
  cat <<EOF
${0}
Start the cpp-best-practices development container '${image_name}:${image_ver}'
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

if [[ $# -ne 0 ]]; then
  usage
  exit 1
fi

set -o xtrace

docker container run -it --rm \
  -v ${PWD}:${container_dir} \
  -e TZ=${TZ} \
  --workdir ${container_dir} \
  ${image_name}:${image_ver}
