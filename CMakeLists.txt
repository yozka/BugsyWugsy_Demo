# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.19)
project ( BugsyWugsy )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS ON)


# Настройки проекта
set( BUILD_SHARED_LIBS OFF 	CACHE BOOL "Статическая сборка" FORCE )

set( SDL_STATIC ON 	CACHE BOOL "Статическая сборка SDL" FORCE )
set( SDL_SHARED OFF CACHE BOOL "Библиотечная сборка SDL" FORCE )




# Include sub-projects.
add_subdirectory (src) 
add_subdirectory (platforms) 
target_compile_definitions (CoreGame PUBLIC EN_ORGANIZATION=\"seragam\")
target_compile_definitions (CoreGame PUBLIC EN_APPLICATION=\"BugsyWugsy\")
target_compile_definitions (CoreGame PUBLIC EN_ENABLE_ASSERT)



# xml
set( tinyxml2_BUILD_TESTING OFF CACHE BOOL "Test xml" FORCE )
add_subdirectory (frameworks/tinyxml2)
target_include_directories (CoreGame PUBLIC frameworks/tinyxml2)
target_link_libraries(BugsyWugsy tinyxml2)

# SDL2
if (NOT EMSCRIPTEN)

add_subdirectory (frameworks/SDL SDL_STATIC)
target_include_directories(CoreGame PUBLIC frameworks/SDL/include)
target_include_directories(BugsyWugsy PUBLIC frameworks/SDL/include)

if(TARGET SDL2::SDL2main)
	target_link_libraries(BugsyWugsy SDL2::SDL2main)
endif()

# SDL_image
set( SDL2IMAGE_SAMPLES OFF CACHE BOOL "Samples image" FORCE )
set( SDL2IMAGE_INSTALL OFF CACHE BOOL "Install image" FORCE )
set( SDL2IMAGE_AVIF_VENDORED OFF 	CACHE BOOL "Статическая сборка SDL" FORCE )
add_subdirectory (frameworks/SDL_image)
target_include_directories(CoreGame PUBLIC frameworks/SDL_image)
target_link_libraries(CoreGame SDL2_image::SDL2_image-static)
#target_link_libraries(BugsyWugsy SDL2_image::SDL2_image-static)

# SDL_ttf
set( SDL2TTF_SAMPLES OFF CACHE BOOL "Freetype Samples" FORCE )
set( SDL2TTF_INSTALL OFF CACHE BOOL "Freetype Install" FORCE )
set( SDL2TTF_VENDORED ON CACHE BOOL "Freetype Vendored" FORCE )
add_subdirectory (frameworks/SDL_ttf)
target_include_directories(CoreGame PUBLIC frameworks/SDL_ttf)
target_link_libraries(BugsyWugsy SDL2_ttf::SDL2_ttf-static)

# SDL_mixer
set( SDL2MIXER_FLAC OFF CACHE BOOL "Flac" FORCE )
set( SDL2MIXER_OPUS OFF CACHE BOOL "Opus" FORCE )
set( SDL2MIXER_SAMPLES OFF CACHE BOOL "Samples" FORCE )
set( SDL2MIXER_INSTALL OFF CACHE BOOL "Install" FORCE )
set( SDL2MIXER_VENDORED ON CACHE BOOL "Vendored" FORCE )
set( SDL2MIXER_WAVPACK_SHARED OFF CACHE BOOL "Wavpack" FORCE )
#set( SDL2MIXER_MOD_XMP_SHARED OFF CACHE BOOL "xmp" FORCE )

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 OLD)
  endif (POLICY CMP0048)
add_subdirectory (frameworks/SDL_mixer)
target_include_directories(CoreGame PUBLIC frameworks/SDL_mixer)
target_link_libraries(CoreGame SDL2_mixer::SDL2_mixer-static)

endif() #

# Engine
target_link_libraries(BugsyWugsy CoreGame)


# Включим ассерты
if (EGG_ASSERT)
	target_compile_definitions (CoreGame 	PUBLIC EN_ENABLE_ASSERT)
	target_compile_definitions (EggEngine 	PUBLIC EN_ENABLE_ASSERT)
endif()


# Настраиваем варнинги
include("cmake/module/warnings.cmake")