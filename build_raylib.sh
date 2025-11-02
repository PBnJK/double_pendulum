#!/bin/bash

set -xe

emcc -c raylib/rcore.c -o raylib/rcore.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c raylib/rshapes.c -o raylib/rshapes.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c raylib/rtextures.c -o raylib/rtextures.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c raylib/rtext.c -o raylib/rtext.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c raylib/rmodels.c -o raylib/rmodels.o -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
emcc -c raylib/utils.c -o raylib/utils.o -Os -Wall -DPLATFORM_WEB
emcc -c raylib/raudio.c -o raylib/raudio.o -Os -Wall -DPLATFORM_WEB

emar rcs raylib/libraylib.a raylib/rcore.o raylib/rshapes.o raylib/rtextures.o raylib/rtext.o raylib/rmodels.o raylib/utils.o raylib/raudio.o
