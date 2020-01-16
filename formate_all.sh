#!/bin/bash

PROCESS_DIRS="cpp_study common"
PROCESS_CMD="clang-format -style=file -i"

find ${PROCESS_DIRS} -regextype posix-extended -regex ".*\.(h|hpp|cpp|cc|proto)" |xargs -I{} -t ${PROCESS_CMD} {}


