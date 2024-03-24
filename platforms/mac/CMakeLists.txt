# mac platform
set( MACOSX ON CACHE BOOL "MACOSX" FORCE )
set( CMAKE_MACOSX_RPATH ON CACHE BOOL "PATH" FORCE )
add_executable(BugsyWugsy main.cpp)

target_compile_definitions (BugsyWugsy PUBLIC EN_PLATFORM_MAC)
target_compile_definitions (BugsyWugsy PUBLIC EN_DESKTOP)

target_compile_definitions (CoreGame PUBLIC EN_PLATFORM_MAC)
target_compile_definitions (CoreGame PUBLIC EN_DESKTOP)

set_target_properties (BugsyWugsy PROPERTIES 
								XCODE_GENERATE_SCHEME TRUE
								XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/assets)


