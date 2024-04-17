# Source game

file(GLOB_RECURSE source_files "*.h" "*.cpp")
add_library (CoreGame ${source_files})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${source_files})

target_include_directories (CoreGame INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories (CoreGame PUBLIC ${CMAKE_CURRENT_LIST_DIR})
