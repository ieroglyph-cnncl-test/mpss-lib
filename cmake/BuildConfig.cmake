#heavily inspired by https://github.com/microsoft/vcpkg/blob/master/scripts/toolchains/windows.cmake
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    add_definitions(-DFMT_HEADER_ONLY)
    add_definitions(-DMPSS_EXPORT_LIB)
    set(MPSS_CRT_LINKAGE "dynamic")
    if(MPSS_CRT_LINKAGE STREQUAL "dynamic")
        set(MPSS_CRT_LINK_FLAG_PREFIX "/MD")
    elseif(MPSS_CRT_LINKAGE STREQUAL "static")
        set(MPSS_CRT_LINK_FLAG_PREFIX "/MT")
    else()
        message(FATAL_ERROR "Invalid setting for MPSS_CRT_LINKAGE: \"${MPSS_CRT_LINKAGE}\". It must be \"static\" or \"dynamic\"")
    endif()

    set(CHARSET_FLAG)
    set(CMAKE_CXX_FLAGS " /nologo /DWIN32 /D_WINDOWS /W3 ${CHARSET_FLAG} /GR /EHsc /MP ${MPSS_CXX_FLAGS}" CACHE STRING "")
    set(CMAKE_C_FLAGS " /nologo /DWIN32 /D_WINDOWS /W3 ${CHARSET_FLAG} /MP ${MPSS_C_FLAGS}" CACHE STRING "")
    set(CMAKE_RC_FLAGS "-c65001 /DWIN32" CACHE STRING "")

    unset(CHARSET_FLAG)

    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG ${MPSS_CRT_LINK_FLAG_PREFIX}d /Z7 /Ob0 /Od /RTC1 ${MPSS_CXX_FLAGS_DEBUG}" CACHE STRING "")
    set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG ${MPSS_CRT_LINK_FLAG_PREFIX}d /Z7 /Ob0 /Od /RTC1 ${MPSS_C_FLAGS_DEBUG}" CACHE STRING "")
    set(CMAKE_CXX_FLAGS_RELEASE "${MPSS_CRT_LINK_FLAG_PREFIX} /O2 /Oi /Gy /DNDEBUG /Z7 ${MPSS_CXX_FLAGS_RELEASE}" CACHE STRING "")
    set(CMAKE_C_FLAGS_RELEASE "${MPSS_CRT_LINK_FLAG_PREFIX} /O2 /Oi /Gy /DNDEBUG /Z7 ${MPSS_C_FLAGS_RELEASE}" CACHE STRING "")

    string(APPEND CMAKE_STATIC_LINKER_FLAGS_RELEASE_INIT " /nologo ")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF ${MPSS_LINKER_FLAGS} ${MPSS_LINKER_FLAGS_RELEASE}" CACHE STRING "")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF ${MPSS_LINKER_FLAGS} ${MPSS_LINKER_FLAGS_RELEASE}" CACHE STRING "")

    string(APPEND CMAKE_STATIC_LINKER_FLAGS_DEBUG_INIT " /nologo ")
    string(APPEND CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT " /nologo ${MPSS_LINKER_FLAGS} ${MPSS_LINKER_FLAGS_DEBUG} ")
    string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT " /nologo ${MPSS_LINKER_FLAGS} ${MPSS_LINKER_FLAGS_DEBUG} ")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g -Wall -Wpedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -Werror -Wpedantic")
endif()

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/bin")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/bin")

