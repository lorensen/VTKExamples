#
# Check if a class exists in VTK. Looks for a .h file for the
# class. If it does not exist, the example is removed from ALL_FILES.
# Usage: Requires_Class name_of_example class_to_be_checked
#
macro(Requires_Class _example _class)
  if (${VTK_VERSION} VERSION_GREATER "8.8")

  # Get the headers for each target
  foreach(_target ${VTK_LIBRARIES})
    get_property(_headers TARGET ${_target} PROPERTY INTERFACE_vtk_module_headers)
    list(APPEND _includes ${_headers})
  endforeach()

  # Remove duplicates
  list(REMOVE_DUPLICATES _includes)

  # See if the header for the class exists
  string(FIND "${_includes}" ${_class}.h _found)

  # If class header does not exists, remove the examples from
  # ALL_FILES and report that the exaple will not be built
  if(_found EQUAL -1)
    message(STATUS "VTKWikiExamples: ${_example} requires VTK class ${_class} and will not be built")
    string(REGEX REPLACE "[^;]*${_example}.cxx"
           "" ALL_FILES "${ALL_FILES}")
    string(REGEX REPLACE "[^;]*${_example}.ui"
           "" ALL_UI_FILES "${ALL_UI_FILES}")
  endif()
  endif()
endmacro()
