# Include platforms

if(WIN32)
	add_subdirectory (windows) 
endif()

if(APPLE AND (${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))
	add_subdirectory (mac) 
endif()

if(APPLE AND (${CMAKE_SYSTEM_NAME} MATCHES "iOS"))
	add_subdirectory (ios) 
endif()

if(ANDROID)
	add_subdirectory (android/app/jni/src) 
endif()

if (DEFINED EMSCRIPTEN)
	add_subdirectory (emscripten) 
endif()