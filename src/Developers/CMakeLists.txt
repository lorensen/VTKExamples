project (${WIKI}Developers)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
endif()

add_executable(Progress Progress.cxx vtkTestFilter.cxx)
target_link_libraries(Progress vtkHybrid)

add_executable(ReaderExample ReaderExample.cxx vtkTestReader.cxx)
target_link_libraries(ReaderExample vtkHybrid)

add_executable(FilterExample FilterExample.cxx vtkTestFilter.cxx)
target_link_libraries(FilterExample vtkHybrid)

add_executable(SourceExample SourceExample.cxx vtkTestSource.cxx)
target_link_libraries(SourceExample vtkHybrid)

add_executable(vtkImageAlgorithmFilterExample vtkImageAlgorithmFilterExample.cxx vtkImageAlgorithmFilter.cxx)
target_link_libraries(vtkImageAlgorithmFilterExample vtkHybrid)

add_executable(vtkImageAlgorithmSourceExample vtkImageAlgorithmSourceExample.cxx vtkImageAlgorithmSource.cxx)
target_link_libraries(vtkImageAlgorithmSourceExample vtkHybrid)
