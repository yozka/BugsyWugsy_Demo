#!/bin/bash

cmake --version >/dev/null 2>&1 || {
    if [ -f /Applications/CMake.app/Contents/bin/cmake-gui ]; then
         echo "CMake doesn't added to PATH. Fixing..."
         sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
         echo "Rerun this script again, please."
    else
         echo "CMake doesn't installed."
    fi
    exit 1;
}

BUILD_DIR=$1
if [ -z "$BUILD_DIR" ]; then
    BUILD_DIR=../build/emscripten
fi

cd "${0%/*}"

# 3.1.0
emsdk install 3.1.26
emsdk activate 3.1.26
#cmake -DCMAKE_TOOLCHAIN_FILE=$EMROOT/cmake/Modules/Platform/Emscripten.cmake ..
emcmake cmake -B "${BUILD_DIR}" -S ..
cmake  --build "${BUILD_DIR}" 
#emmake make -j4 "${BUILD_DIR}"

cp ${BUILD_DIR}/platforms/emscripten/BugsyWugsy.js ../docs/BugsyWugsy.js
cp ${BUILD_DIR}/platforms/emscripten/BugsyWugsy.wasm ../docs/BugsyWugsy.wasm
cp ${BUILD_DIR}/platforms/emscripten/BugsyWugsy.data ../docs/BugsyWugsy.data

