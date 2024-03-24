# Windows platform

add_executable(EggEngine WIN32 main.cpp)

target_compile_definitions (EggEngine PUBLIC EN_PLATFORM_WIN)
target_compile_definitions (EggEngine PUBLIC EN_DESKTOP)

target_compile_definitions (CoreGame PUBLIC EN_PLATFORM_WIN)
target_compile_definitions (CoreGame PUBLIC EN_DESKTOP)


set_target_properties ( EggEngine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/base)

