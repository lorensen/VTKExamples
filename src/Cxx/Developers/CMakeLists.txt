PROJECT (${WIKI}Developers)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_USE_RENDERING)
  MESSAGE(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
ENDIF(NOT VTK_USE_RENDERING)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  SET(KIT_LIBS vtkRendering vtkHybrid)
else()
  SET(KIT_LIBS ${VTK_LIBRARIES})
endif()
#

ADD_EXECUTABLE(AlgorithmFilter AlgorithmFilter vtkTestAlgorithmFilter vtkTest)
TARGET_LINK_LIBRARIES(AlgorithmFilter ${VTK_LIBRARIES})

ADD_EXECUTABLE(AlgorithmSource AlgorithmSource vtkTestAlgorithmSource vtkTest1)
TARGET_LINK_LIBRARIES(AlgorithmSource ${VTK_LIBRARIES})

ADD_EXECUTABLE(ProgressReport ProgressReport.cxx vtkTestProgressReportFilter.cxx)
TARGET_LINK_LIBRARIES(ProgressReport ${VTK_LIBRARIES})

ADD_EXECUTABLE(FilterSelfProgress FilterSelfProgress.cxx vtkTestFilterSelfProgressFilter.cxx)
TARGET_LINK_LIBRARIES(FilterSelfProgress ${VTK_LIBRARIES})

ADD_EXECUTABLE(GraphAlgorithmFilter GraphAlgorithmFilter vtkTestGraphAlgorithmFilter.cxx)
TARGET_LINK_LIBRARIES(GraphAlgorithmFilter ${VTK_LIBRARIES})

ADD_EXECUTABLE(GraphAlgorithmSource GraphAlgorithmSource vtkTestGraphAlgorithmSource.cxx)
TARGET_LINK_LIBRARIES(GraphAlgorithmSource ${VTK_LIBRARIES})

ADD_EXECUTABLE(ImageAlgorithmFilter ImageAlgorithmFilter vtkImageAlgorithmFilter.cxx)
TARGET_LINK_LIBRARIES(ImageAlgorithmFilter ${VTK_LIBRARIES})

ADD_EXECUTABLE(MultipleInputPorts MultipleInputPorts vtkTestMultipleInputPortsFilter)
TARGET_LINK_LIBRARIES(MultipleInputPorts ${VTK_LIBRARIES})
