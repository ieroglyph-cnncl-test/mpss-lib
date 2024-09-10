#pragma once

#if defined(_WIN32) && !defined(WIN32)
#    define WIN32
#endif
#if defined WIN32 && !defined(__MINGW32__)
#    if defined MPSS_EXPORT_LIB
#        define MPSS_EXPORT __declspec(dllexport)
#    else
#        define MPSS_EXPORT __declspec(dllimport)
#    endif
#else
  #define MPSS_EXPORT 
#endif
