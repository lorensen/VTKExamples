project (${WIKI}Developers)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif()
include(${VTK_USE_FILE})
endif()

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkRendering vtkHybrid)
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()
#

add_executable(AlgorithmFilter AlgorithmFilter vtkTestAlgorithmFilter vtkTest)
target_link_libraries(AlgorithmFilter ${VTK_LIBRARIES})

add_executable(AlgorithmSource AlgorithmSource vtkTestAlgorithmSource vtkTest1)
target_link_libraries(AlgorithmSource ${VTK_LIBRARIES})

add_executable(ProgressReport ProgressReport.cxx vtkTestProgressReportFilter.cxx)
target_link_libraries(ProgressReport ${VTK_LIBRARIES})

add_executable(FilterSelfProgress FilterSelfProgress.cxx vtkTestFilterSelfProgressFilter.cxx)
target_link_libraries(FilterSelfProgress ${VTK_LIBRARIES})

add_executable(GraphAlgorithmFilter GraphAlgorithmFilter vtkTestGraphAlgorithmFilter.cxx)
target_link_libraries(GraphAlgorithmFilter ${VTK_LIBRARIES})

add_executable(GraphAlgorithmSource GraphAlgorithmSource vtkTestGraphAlgorithmSource.cxx)
target_link_libraries(GraphAlgorithmSource ${VTK_LIBRARIES})

add_executable(ImageAlgorithmFilter ImageAlgorithmFilter vtkImageAlgorithmFilter.cxx)
target_link_libraries(ImageAlgorithmFilter ${VTK_LIBRARIES})

add_executable(MultipleInputPorts MultipleInputPorts vtkTestMultipleInputPortsFilter)
target_link_libraries(MultipleInputPorts ${VTK_LIBRARIES})
