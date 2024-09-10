#pragma once

#ifdef _WIN32
  #if defined MPSS_EXPORT_LIB
    #define MPSS_EXPORT __declspec(dllexport)
  #else
    #define MPSS_EXPORT __declspec(dllimport)
  #endif
#else
  #define MPSS_EXPORT 
#endif
