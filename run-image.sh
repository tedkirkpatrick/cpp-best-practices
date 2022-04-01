#!/usr/bin/env bash
# Run the cpp-best-practices dev environment as a container
set -o nounset
set -o errexit

image_name=cpp_best
image_ver=2022.4

TZ=${TZ:-Canada/Pacific}

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
  -v ${PWD}:/home/cpp_bp \
  -e TZ=${TZ} \
  --workdir /home/cpp_bp \
  ${image_name}:${image_ver}
