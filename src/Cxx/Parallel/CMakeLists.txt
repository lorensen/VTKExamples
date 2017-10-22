project (${WIKI}Parallel)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_PARALLEL)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkHybrid vtkWidgets)
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

# Testing
set(KIT Parallel)
set(NEEDS_ARGS

)
include(${WikiExamples_SOURCE_DIR}/CMake/ExamplesTesting.cmake)

set(DATA ${WikiExamples_SOURCE_DIR}/src/Testing/Data)
set(TEMP ${WikiExamples_BINARY_DIR}/Testing/Temporary)

