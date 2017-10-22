
#
# This CMake module implements the logic required to build this project
# following commit kitware/VTK@061eff0 from October 18th 2017.
#
# The VTK build system was one of the first modular one to be setup and
# didn't allow to build VTK module as standalone project so that
# they could be packaged independently and also depended one for buidling
# other modules.
#

if(${VTK_VERSION} VERSION_LESS "8.1")
  return()
endif()

get_filename_component(WikiExample_MODULE_CONFIG ${CMAKE_CURRENT_LIST_FILE} NAME_WE)
message(STATUS "VTKWikiExamples:")
message(STATUS "VTKWikiExamples: Including VTK using: ${WikiExample_MODULE_CONFIG}")
message(STATUS "VTKWikiExamples:")

if(NOT VTK_BINARY_DIR)
  include(vtkExternalModuleMacros)
else()
  set(VTK_USE_FILE ${VTK_CMAKE_DIR}/UseVTK.cmake)
endif()

# Load up the CMake variables we need.
vtk_module_export_info()

# If available, load optional VTK modules.
foreach(optional_dep IN LISTS WikiExamples_OPTIONAL_DEPENDS)
  list(FIND VTK_MODULES_AVAILABLE ${optional_dep} found)
  if (found GREATER -1)
    list(APPEND ${vtk-module}_DEPENDS ${optional_dep})
  endif()
endforeach()

# Load requested modules and their dependencies into
# variables VTK_(DEFINITIONS|LIBRARIES|INCLUDE_DIRS|LIBRARY_DIRS).
vtk_module_config(VTK ${${vtk-module}_DEPENDS})

# Since this project does not use the regular VTK module API
# to build the test executables (i.e. vtk_module_test_executable), the
# required compile definitions (i.e. <module>_AUTOINIT macros needed for
# object factory overrides initialization) are not automatically used.
#
# To address this, including VTK_USE_FILE ensures the compile definitions
# are explicitly associated with the top-level project directory.
include(${VTK_USE_FILE})
