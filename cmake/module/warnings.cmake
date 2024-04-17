#disbled warnings for libs

#WINDOWS
if(WIN32)

    #xmp_shared
    target_compile_options (xmp_shared PRIVATE /W0)

endif()


#MAC
if(APPLE AND (${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))

    target_compile_options(wavpack PRIVATE -Wno-shorten-64-to-32)
    #target_compile_options(xmp_shared PRIVATE -Wno-shorten-64-to-32)

endif()


#IOS
if(APPLE AND (${CMAKE_SYSTEM_NAME} MATCHES "iOS"))
endif()


#ANDROID
if(ANDROID)
endif()





