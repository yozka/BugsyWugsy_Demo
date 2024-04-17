# Windows platform

add_executable(BugsyWugsy WIN32 main.cpp)

target_compile_definitions (BugsyWugsy PUBLIC EN_PLATFORM_WIN)
target_compile_definitions (BugsyWugsy PUBLIC EN_DESKTOP)

target_compile_definitions (CoreGame PUBLIC EN_PLATFORM_WIN)
target_compile_definitions (CoreGame PUBLIC EN_DESKTOP)


set_target_properties ( BugsyWugsy PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/assets)

