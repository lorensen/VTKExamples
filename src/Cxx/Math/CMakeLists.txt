project (${WIKI}Math)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkHybrid)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#
# Build all .cxx files in the directory
file(GLOB ALL_FILES *.cxx)
foreach(SOURCE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${SOURCE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
endforeach()

if (BUILD_TESTING)
# Testing
set(KIT Math)
set(NEEDS_ARGS
)
include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)
endif()
