#!/bin/bash

set -xe

emcc -o web/double_pendulum.js src/main.c -Os -Wall -Wextra -pedantic raylib/libraylib.a -I./inc/ -L./raylib -sUSE_GLFW=3 -sASYNCIFY -sASSERTIONS=1 -sWASM=1 -sEXPORTED_RUNTIME_METHODS=ccall -DPLATFORM_WEB -lraylib -lm
