# emscripten platform

add_executable(BugsyWugsy main.cpp)

add_compile_definitions("__EMSCRIPTEN__")

#
#target_link_options(${PROJECT_NAME} PRIVATE
#"-sMODULARIZE=1"
#"-sEXPORT_NAME='Main'"
#"-sINVOKE_RUN=0"
#"-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0"
#"-sEXPORTED_FUNCTIONS=['_main']"
#"-sEXPORTED_RUNTIME_METHODS=['callMain', 'ccall', 'cwrap']"
#"-sFORCE_FILESYSTEM=1"
#"-sUSE_SDL=2"
#"-sUSE_WEBGL2"
#"-sALLOW_MEMORY_GROWTH=1" 
#"-sASYNCIFY"
#"-Os"
#"-sSTACK_SIZE=5MB"
#)
#


#set(CMAKE_EXECUTABLE_SUFFIX ".wasm")

#set_target_properties(BugsyWugsy PROPERTIES COMPILE_FLAGS "-Os -sSIDE_MODULE=1 ")
#set_target_properties(BugsyWugsy PROPERTIES LINK_FLAGS    "-DLIBCXXABI_ENABLE_PIC:BOOL=ON -Os -sWASM=1 -sMODULARIZE=1 -sSIDE_MODULE=1 -sSTANDALONE_WASM --no-entry -sUSE_SDL=2 -sUSE_WEBGL2 -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 -sALLOW_MEMORY_GROWTH=1 -sFORCE_FILESYSTEM=1 -sASYNCIFY")

#set_target_properties(CoreGame PROPERTIES COMPILE_FLAGS "-Os -s SIDE_MODULE=1 ")
#set_target_properties(CoreGame PROPERTIES LINK_FLAGS    "-Os -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry -s USE_SDL=2")



#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -USE_SDL=2 -USE_FREETYPE=1")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS=['png','jpeg'] -sUSE_SDL_MIXER=2 -sUSE_OGG=1 -sUSE_VORBIS=1 -sUSE_SDL_TTF=2 -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sFORCE_FILESYSTEM=1 -sDEMANGLE_SUPPORT=1")
set(SDL2_LIBRARIES "-sUSE_SDL=2")
set(SDL2_IMAGE_LIBRARIES "-sUSE_SDL_IMAGE=2")
set(SDL2_MIXER_LIBRARIES "-sUSE_SDL_MIXER=2")
set(SDL2_TTF_LIBRARIES "-sUSE_SDL_TTF=2")
set(SDL2_LINKERS "--preload-file ${CMAKE_SOURCE_DIR}/assets@/")
target_link_libraries(BugsyWugsy ${SDL2_LINKERS} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})

target_compile_definitions (BugsyWugsy PUBLIC EN_PLATFORM_EMSCRIPTEN)
target_compile_definitions (BugsyWugsy PUBLIC EN_DESKTOP)

target_compile_definitions (CoreGame PUBLIC EN_PLATFORM_EMSCRIPTEN)
target_compile_definitions (CoreGame PUBLIC EN_DESKTOP)

target_compile_definitions (BugsyWugsy PUBLIC SCREEN_WIDTH=640)
target_compile_definitions (BugsyWugsy PUBLIC SCREEN_HEIGHT=480)

#set_target_properties(BugsyWugsy PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/assets --use-preload-plugins")