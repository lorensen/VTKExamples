
#
# Following the improvement of VTK build system integrated in
# commit kitware/VTK@061eff0 from October 18th 2017 the approach
# implemented in this CMake module stopped working.
#

if(${VTK_VERSION} VERSION_EQUAL "8.1" OR ${VTK_VERSION} VERSION_GREATER "8.1")
  return()
endif()

#
# This CMake module implements the legacy logic that is used
# to find and load the VTK dependencies needed by this project.
#

#
# It set thes variable `WikiModuleConfigLegacy_RETURN` to 1 in the
# including scope to indicate that "return()" should be called.
#

get_filename_component(_name ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
message(STATUS "VTKWikiExamples:")
message(STATUS "VTKWikiExamples: Including VTK using: ${_name}")
message(STATUS "VTKWikiExamples:")

set(${_name}_RETURN 0)

if(Module_WikiExamples)
  #
  # This is a VTK remote module build
  #

  vtk_module_impl()
  if(NOT EXISTS "${VTK_BINARY_DIR}/VTKConfig.cmake")
    set(${_name}_RETURN 1)
    return()
  endif()

  find_package(VTK PATHS ${VTK_BINARY_DIR})
  include(${VTK_USE_FILE})
else()
  #
  # This is a stand-alone build
  #

  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

