#!/bin/bash

PROCESS_DIRS="common src shell"
PROCESS_CMD="clang-format -style=file -i"

find ${PROCESS_DIRS} -regextype posix-extended -regex ".*\.(h|hpp|cpp|cc|c|proto)" |xargs -I{} -t ${PROCESS_CMD} {}
