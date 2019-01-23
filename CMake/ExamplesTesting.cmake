#
# Create tests for examples
#
if (BUILD_TESTING)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set(MyTests "")
foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  list(FIND EXCLUDE_TEST ${EXAMPLE} EXCLUDED)
  set(MyTests ${MyTests} Test${EXAMPLE}.cxx)
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/Test${EXAMPLE}.cxx
    "#define main Test${EXAMPLE}\n#include \"${EXAMPLE}.cxx\"\n")
  if(EXCLUDED EQUAL -1)
    list(FIND NEEDS_ARGS ${EXAMPLE} SKIP_ADD)
    if(SKIP_ADD EQUAL -1)
      add_test(${KIT}-${EXAMPLE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${KIT}CxxTests Test${EXAMPLE})
    endif()
    set_property(TEST ${KIT}-${EXAMPLE} PROPERTY LABELS WikiExamples)
  endif()
endforeach()
set(VTK_BINARY_DIR ${WikiExamples_BINARY_DIR})
set(VTK_DATA_ROOT ${WikiExamples_SOURCE_DIR}/src/Testing)
include(${WikiExamples_SOURCE_DIR}/CMake/vtkTestingObjectFactory.cmake)
add_executable(${KIT}CxxTests ${KIT}CxxTests.cxx
               ${MyTests})
target_link_libraries(${KIT}CxxTests ${KIT_LIBS})
if (VTK_VERSION VERSION_GREATER "8.8")
  vtk_module_autoinit(
    TARGETS ${KIT}CxxTests
    MODULES ${VTK_LIBRARIES}
    )
endif()
endif()