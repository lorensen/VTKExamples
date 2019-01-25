# CMake policies for the wiki examples
#-----------------------------------------------------------------------------

# Set policies as needed.
foreach(p
    CMP0020 # CMake 2.8.11
    CMP0022 # CMake 2.8.12
    CMP0025 # CMake 3.0
    CMP0043 # CMake 3.0
    CMP0053 # CMake 3.1
    CMP0071
      )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()
