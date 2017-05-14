PROJECT (${WIKI}Developers)

IF(NOT WikiExamples_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT WikiExamples_BINARY_DIR)

ADD_EXECUTABLE(Progress Progress.cxx vtkTestFilter.cxx)
TARGET_LINK_LIBRARIES(Progress vtkHybrid)

ADD_EXECUTABLE(ReaderExample ReaderExample.cxx vtkTestReader.cxx)
TARGET_LINK_LIBRARIES(ReaderExample vtkHybrid)

ADD_EXECUTABLE(FilterExample FilterExample.cxx vtkTestFilter.cxx)
TARGET_LINK_LIBRARIES(FilterExample vtkHybrid)

ADD_EXECUTABLE(SourceExample SourceExample.cxx vtkTestSource.cxx)
TARGET_LINK_LIBRARIES(SourceExample vtkHybrid)

ADD_EXECUTABLE(vtkImageAlgorithmFilterExample vtkImageAlgorithmFilterExample.cxx vtkImageAlgorithmFilter.cxx)
TARGET_LINK_LIBRARIES(vtkImageAlgorithmFilterExample vtkHybrid)

ADD_EXECUTABLE(vtkImageAlgorithmSourceExample vtkImageAlgorithmSourceExample.cxx vtkImageAlgorithmSource.cxx)
TARGET_LINK_LIBRARIES(vtkImageAlgorithmSourceExample vtkHybrid)
