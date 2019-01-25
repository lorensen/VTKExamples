project (${WIKI}Developers)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonCore
    vtkCommonDataModel
    vtkCommonExecutionModel
    vtkFiltersSources
    vtkInfovisCore
    QUIET
    )
  if (VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

add_executable(AlgorithmFilter AlgorithmFilter vtkTestAlgorithmFilter vtkTest)
target_link_libraries(AlgorithmFilter ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS AlgorithmFilter
    MODULES ${VTK_LIBRARIES}
    )
endif()

add_executable(AlgorithmSource AlgorithmSource vtkTestAlgorithmSource vtkTest1)
target_link_libraries(AlgorithmSource ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS AlgorithmSource
    MODULES ${VTK_LIBRARIES}
    )
endif()

add_executable(ProgressReport ProgressReport.cxx vtkTestProgressReportFilter.cxx)
target_link_libraries(ProgressReport ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS ProgressReport
    MODULES ${VTK_LIBRARIES}
    )
endif()

add_executable(FilterSelfProgress FilterSelfProgress.cxx vtkTestFilterSelfProgressFilter.cxx)
target_link_libraries(FilterSelfProgress ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS FilterSelfProgress
    MODULES ${VTK_LIBRARIES}
    )
endif()

add_executable(GraphAlgorithmFilter GraphAlgorithmFilter vtkTestGraphAlgorithmFilter.cxx)
target_link_libraries(GraphAlgorithmFilter ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS GraphAlgorithmFilter
    MODULES ${VTK_LIBRARIES}
    )
endif()

add_executable(GraphAlgorithmSource GraphAlgorithmSource vtkTestGraphAlgorithmSource.cxx)
target_link_libraries(GraphAlgorithmSource ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS GraphAlgorithmSource
    MODULES ${VTK_LIBRARIES}
    )
endif()

add_executable(ImageAlgorithmFilter ImageAlgorithmFilter vtkImageAlgorithmFilter.cxx)
target_link_libraries(ImageAlgorithmFilter ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS ImageAlgorithmFilter
    MODULES ${VTK_LIBRARIES}
    )
endif()

add_executable(MultipleInputPorts MultipleInputPorts vtkTestMultipleInputPortsFilter)
target_link_libraries(MultipleInputPorts ${VTK_LIBRARIES})
if (NOT VTK_VERSION VERSION_LESS "8.90.0")
  vtk_module_autoinit(
    TARGETS MultipleInputPorts
    MODULES ${VTK_LIBRARIES}
    )
endif()
