#
# These checks are compatible witk ITK's checks
#

# On Visual Studio 8 MS deprecated C. This removes all 1.276E1265 security
# warnings
if(WIN32)
   if(NOT MINGW)
     add_definitions(
       -D_CRT_FAR_MAPPINGS_NO_DEPRECATE
       -D_CRT_IS_WCTYPE_NO_DEPRECATE
       -D_CRT_MANAGED_FP_NO_DEPRECATE
       -D_CRT_NONSTDC_NO_DEPRECATE
       -D_CRT_SECURE_NO_DEPRECATE
       -D_CRT_SECURE_NO_DEPRECATE_GLOBALS
       -D_CRT_SETERRORMODE_BEEP_SLEEP_NO_DEPRECATE
       -D_CRT_TIME_FUNCTIONS_NO_DEPRECATE
       -D_CRT_VCCLRIT_NO_DEPRECATE
       -D_SCL_SECURE_NO_DEPRECATE
       )
   endif()
endif()

if(WIN32)
  # Some libraries have no dllexport markup, so we can
  # build full shared libraries only with the GNU toolchain.
  #  if(CMAKE_COMPILER_IS_GNUCXX)
    # CMake adds --enable-all-exports on Cygwin (since Cygwin is
    # supposed to be UNIX-like), but we need to add it explicitly for
    # a native windows build with the MinGW tools.
    if(MINGW)
      set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS
        "-shared -Wl,--export-all-symbols -Wl,--enable-auto-import")
      set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS
        "-shared -Wl,--export-all-symbols -Wl,--enable-auto-import")
      set(CMAKE_EXE_LINKER_FLAGS "-Wl,--enable-auto-import")
    endif()
endif()
