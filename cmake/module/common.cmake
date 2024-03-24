
if(__DEPENDENCIES_COMMON_INCLUDED)
    return()
endif(__DEPENDENCIES_COMMON_INCLUDED)
set(__DEPENDENCIES_COMMON_INCLUDED TRUE)

set(DEPENDENCIES_IDE_FOLDER "dependencies")

if(__MKR_MIN_SYSTEM_VERSION)
    set(DEPENDENCIES_MIN_SYSTEM_VERSION ${__MKR_MIN_SYSTEM_VERSION})
elseif(WIN_UWP)
    set(DEPENDENCIES_MIN_SYSTEM_VERSION "10.0.15063.0")
endif()


function(dependencies_check_cpp_exceptions _OUT_IS_ENABLED)
    if(WIN32)
        if(CMAKE_CXX_FLAGS MATCHES "(^| )/EH[scar]+( |$)")
            set(${_OUT_IS_ENABLED} TRUE PARENT_SCOPE)
        else()
            set(${_OUT_IS_ENABLED} FALSE PARENT_SCOPE)
        endif()

    else()
        if(CMAKE_CXX_FLAGS MATCHES "(^| )-fno-exceptions( |$)")
            set(${_OUT_IS_ENABLED} FALSE PARENT_SCOPE)
        else()
            set(${_OUT_IS_ENABLED} TRUE PARENT_SCOPE)
        endif()

    endif()
endfunction(dependencies_check_cpp_exceptions)


function(dependencies_target_include_sysdir _IN_TARGET_NAME _IN_INCLUDES_PATH)
    if(WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if(NOT MAKER_DISABLE_WIN_LLVM_IMSVC_OPTION)
            target_compile_options(${_IN_TARGET_NAME} INTERFACE /imsvc${_IN_INCLUDES_PATH})
        endif()
        target_include_directories(${_IN_TARGET_NAME} INTERFACE ${_IN_INCLUDES_PATH})
    else()
        target_include_directories(${_IN_TARGET_NAME} SYSTEM INTERFACE ${_IN_INCLUDES_PATH})
    endif()
endfunction(dependencies_target_include_sysdir)


function(dependencies_target_include_dir _IN_TARGET_NAME _IN_INCLUDES_PATH _IN_INTERFACE_AS_SYSDIR)
    get_property(TARGET_TYPE TARGET ${_IN_TARGET_NAME} PROPERTY TYPE)
    if(TARGET_TYPE STREQUAL "INTERFACE_LIBRARY")
        if(_IN_INTERFACE_AS_SYSDIR)
            dependencies_target_include_sysdir(${_IN_TARGET_NAME} ${_IN_INCLUDES_PATH})
        else()
            target_include_directories(${_IN_TARGET_NAME} INTERFACE ${_IN_INCLUDES_PATH})
        endif()
    else()
        if(_IN_INTERFACE_AS_SYSDIR)
            target_include_directories(${_IN_TARGET_NAME} PRIVATE ${_IN_INCLUDES_PATH})
            dependencies_target_include_sysdir(${_IN_TARGET_NAME} ${_IN_INCLUDES_PATH})
        else()
            target_include_directories(${_IN_TARGET_NAME} PUBLIC ${_IN_INCLUDES_PATH})
        endif()
    endif()
endfunction(dependencies_target_include_dir)


function(dependencies_create_target_apple _IN_TARGET_NAME _IN_LIB_BASE_PATH _IN_LIB_BASE_FILE_NAME _IN_INCLUDES_PATH)
    get_filename_component(LINK_LIB_BASE_PATH "${_IN_LIB_BASE_PATH}" ABSOLUTE)
    add_library(${_IN_TARGET_NAME} INTERFACE)
    target_link_libraries(${_IN_TARGET_NAME} INTERFACE "${LINK_LIB_BASE_PATH}/$(LIBCONFIG)$(EFFECTIVE_PLATFORM_NAME)/lib${_IN_LIB_BASE_FILE_NAME}.a")

    if(_IN_INCLUDES_PATH)
        get_filename_component(INC_PATH "${_IN_INCLUDES_PATH}" ABSOLUTE)
        if(ENGINE_SYSTEM_INCLUDE_DIRS)
            target_include_directories(${_IN_TARGET_NAME} SYSTEM INTERFACE ${INC_PATH})
        else()
            target_include_directories(${_IN_TARGET_NAME} INTERFACE ${INC_PATH})
        endif()
    endif()
endfunction(dependencies_create_target_apple)


function(dependencies_create_target_windows _IN_TARGET_NAME _IN_LIB_BASE_PATH_VC _IN_LIB_BASE_FILE_NAME _IN_INCLUDES_PATH)
    cmake_parse_arguments(__DEPS "" "SUBDIRECTORY" "" "${ARGN}")
    string(REGEX MATCH "^[^,]*" TOOLSET_VERSION "${CMAKE_GENERATOR_TOOLSET}")
    if (TOOLSET_VERSION STREQUAL "v142" OR CMAKE_GENERATOR_TOOLSET STREQUAL "LLVM_v142" OR CMAKE_GENERATOR_TOOLSET STREQUAL "ClangCL")
        get_filename_component(LINK_LIB_BASE_PATH "${_IN_LIB_BASE_PATH_VC}14.2" ABSOLUTE)
    else()
        message(FATAL_ERROR "Unknown toolset: ${CMAKE_GENERATOR_TOOLSET}")
        return()
    endif()

    if(__DEPS_SUBDIRECTORY)
        set(LINK_LIB_BASE_PATH "${LINK_LIB_BASE_PATH}/${__DEPS_SUBDIRECTORY}")
    endif()

    if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
        set(LINK_LIB_BASE_PATH "${LINK_LIB_BASE_PATH}/x64")
    endif()

    add_library(${_IN_TARGET_NAME} INTERFACE)
    if(EXISTS "${LINK_LIB_BASE_PATH}/${_IN_LIB_BASE_FILE_NAME}d.lib")
        target_link_libraries(${_IN_TARGET_NAME} INTERFACE debug     "${LINK_LIB_BASE_PATH}/${_IN_LIB_BASE_FILE_NAME}d.lib"
                                                           optimized "${LINK_LIB_BASE_PATH}/${_IN_LIB_BASE_FILE_NAME}.lib")
    else()
        target_link_libraries(${_IN_TARGET_NAME} INTERFACE "${LINK_LIB_BASE_PATH}/${_IN_LIB_BASE_FILE_NAME}.lib")
    endif()

    if(_IN_INCLUDES_PATH)
        get_filename_component(INC_PATH "${_IN_INCLUDES_PATH}" ABSOLUTE)
        if(ENGINE_SYSTEM_INCLUDE_DIRS)
            dependencies_target_include_sysdir(${_IN_TARGET_NAME} ${INC_PATH})
        else()
            target_include_directories(${_IN_TARGET_NAME} INTERFACE ${INC_PATH})
        endif()
    endif()
endfunction(dependencies_create_target_windows)


function(dependencies_target_compile_definitions _IN_TARGET_NAME)
    cmake_parse_arguments(__DEPS "" "" "COMMON_DEFINITIONS;DEBUG_DEFINITIONS;RELEASE_DEFINITIONS" "${ARGN}")
    if(__DEPS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments: ${__DEPS_UNPARSED_ARGUMENTS}")
    endif()

    set(RESULT_DEFINITIONS_EXPRESSION ${__DEPS_COMMON_DEFINITIONS})
    get_property(DEBUG_CFGS GLOBAL PROPERTY DEBUG_CONFIGURATIONS)
    foreach(CFG IN LISTS CMAKE_CONFIGURATION_TYPES)
        if(CFG STREQUAL "Debug" OR CFG IN_LIST DEBUG_CFGS)
            list(APPEND RESULT_DEFINITIONS_EXPRESSION "$<$<CONFIG:${CFG}>:${__DEPS_DEBUG_DEFINITIONS}>")
        else()
            list(APPEND RESULT_DEFINITIONS_EXPRESSION "$<$<CONFIG:${CFG}>:${__DEPS_RELEASE_DEFINITIONS}>")
        endif()
    endforeach(CFG)
    target_compile_definitions(${_IN_TARGET_NAME} PRIVATE ${RESULT_DEFINITIONS_EXPRESSION})
endfunction(dependencies_target_compile_definitions)


function(dependencies_target_common_configuration _IN_TARGET_NAME)
    cmake_parse_arguments(__DEPS "" "" "SOURCE_FILES;HEADER_FILES" ${ARGN})
    if(__DEPS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments: ${__DEPS_UNPARSED_ARGUMENTS}")
    endif()

    if(__DEPS_SOURCE_FILES OR __DEPS_HEADER_FILES)
        if(NOT ${CMAKE_VERSION} VERSION_LESS "3.8.0")
            # TREE появилось в cmake 3.8.*
            # Более старая версия может используется в Andorid(3.6), а так же Linux, но тут раскладка для студий не важна.
            source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${__DEPS_SOURCE_FILES} ${__DEPS_HEADER_FILES})
        endif()

        set_source_files_properties(${__DEPS_SOURCE_FILES} ${__DEPS_HEADER_FILES} PROPERTIES XCODE_EXPLICIT_FILE_TYPE "-")

        if(__DEPS_HEADER_FILES)
            list(FILTER __DEPS_HEADER_FILES INCLUDE REGEX "^.*(\\.cpp|\\.cxx|\\.cc|\\.c|\\.mm|\\.m)$")
            set_source_files_properties(${__DEPS_HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
        endif()
    endif()

    set_target_properties(${_IN_TARGET_NAME} PROPERTIES FOLDER "${DEPENDENCIES_IDE_FOLDER}")

    # Поддержка сборки архива под Xcode.
    if(APPLE)
        if((DEFINED CMAKE_XCODE_BUILD_SYSTEM) AND (CMAKE_XCODE_BUILD_SYSTEM EQUAL 12))
            set(DEFAULT_APPLE_OUTPUT_DIR ${MAKER_APPLE_NBS_DEFAULT_BUILD_OUT_DIR})
            set(DEFAULT_APPLE_TMP_DIR ${MAKER_APPLE_NBS_DEFAULT_TMP_OUT_DIR})
        else()
            set(DEFAULT_APPLE_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>$(EFFECTIVE_PLATFORM_NAME)")
            set(DEFAULT_APPLE_TMP_DIR "")
        endif()
        set_target_properties(${_IN_TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${DEFAULT_APPLE_OUTPUT_DIR}"
                                                            LIBRARY_OUTPUT_DIRECTORY "${DEFAULT_APPLE_OUTPUT_DIR}"
                                                            ARCHIVE_OUTPUT_DIRECTORY "${DEFAULT_APPLE_OUTPUT_DIR}")


        if(DEFAULT_APPLE_TMP_DIR)
            set_property(TARGET ${_IN_TARGET_NAME} PROPERTY XCODE_ATTRIBUTE_TARGET_TEMP_DIR "${DEFAULT_APPLE_TMP_DIR}/${_IN_TARGET_NAME}.build")
        endif()

        # Настраиваем исключения, синхронизируем таргет с опциями компиляции
        if(CMAKE_GENERATOR STREQUAL "Xcode")
            if(CMAKE_CXX_FLAGS MATCHES "(^| )-fexceptions( |$)") # Мы явно включили исключения
                __maker_set_xcode_property(${_IN_TARGET_NAME} GCC_ENABLE_CPP_EXCEPTIONS YES)
            elseif(CMAKE_CXX_FLAGS MATCHES "(^| )-fno-exceptions( |$)") # Мы явно отключили исключения
                __maker_set_xcode_property(${_IN_TARGET_NAME} GCC_ENABLE_CPP_EXCEPTIONS NO)
            endif()
        endif()
    endif()

    # Общие настройки под Xcode
    set_property(TARGET ${_IN_TARGET_NAME} PROPERTY XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN      YES)
    set_property(TARGET ${_IN_TARGET_NAME} PROPERTY XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN          YES)

    set(DEPENDENCIES_WIN32_WINNT "0x0600")
    set(DEPENDENCIES_UWP_WINNT   "0x0603")

    # Общие настройки под Win
    if(WIN_UWP OR WIN32)
        get_property(TARGET_TYPE TARGET ${_IN_TARGET_NAME} PROPERTY TYPE)
        if(NOT TARGET_TYPE STREQUAL "UTILITY")
            target_compile_definitions(${_IN_TARGET_NAME} PRIVATE "WIN32_LEAN_AND_MEAN")

            if(WIN_UWP)
                target_compile_definitions(${_IN_TARGET_NAME} PRIVATE "_WIN32_WINNT=${DEPENDENCIES_UWP_WINNT}")
                set_target_properties(${_IN_TARGET_NAME} PROPERTIES VS_WINDOWS_TARGET_PLATFORM_MIN_VERSION "${DEPENDENCIES_MIN_SYSTEM_VERSION}"
                                                                    VS_WINRT_COMPONENT ON)
            else()
                target_compile_definitions(${_IN_TARGET_NAME} PRIVATE "_WIN32_WINNT=${DEPENDENCIES_WIN32_WINNT}")
            endif()
        endif()
    endif()

    # Сохраняем путь до исходников библиотеки.
    # Используется в release/* ветках, чтобы определить необходимость делать touch для исходников библиотеки из dependencies
    # когда переключаемся с master на release/*. Это необходимо чтобы тригернуть сборку библиотек когда папка dependencies не удалялась.
    string(MD5 TARGET_NAME_HASH "${_IN_TARGET_NAME}")
    set(__DEPS_${TARGET_NAME_HASH}_PREVIOUS_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "${_IN_TARGET_NAME} target's previous source directory")

    #/------------------------statistics_collector-----------------------------/
    if(TARGET STATISTICS_COLLECTOR)
        get_property(TARGET_TYPE TARGET ${_IN_TARGET_NAME} PROPERTY TYPE)
        if(NOT TARGET_TYPE STREQUAL "UTILITY")
            __maker_do_collect_statistics(${_IN_TARGET_NAME} STATIC_LIB)
        endif()
    endif()
    #/------------------------statistics_collector-----------------------------/
endfunction(dependencies_target_common_configuration)
