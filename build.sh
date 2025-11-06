#!/bin/bash

set -xe

emcc -o web/double_pendulum.js src/main.c -Os -Wall -Wextra -pedantic -I ~/emsdk/upstream/emscripten/cache/sysroot/include \
	-L ~/emsdk/upstream/emscripten/cache/sysroot/lib/libraylib.a -s USE_GLFW=3 -s ASYNCIFY -s WASM=1 -sEXPORTED_RUNTIME_METHODS=ccall \
	-DPLATFORM_WEB ~/emsdk/upstream/emscripten/cache/sysroot/lib/libraylib.a
