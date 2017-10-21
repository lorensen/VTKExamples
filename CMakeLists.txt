cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
if (POLICY CMP0057)
  cmake_policy(SET CMP0057 NEW)
endif()

PROJECT(WikiExamples)

# Display type of build
set(_msg "VTKWikiExamples: Building VTKWikiExamples stand-alone")
message(STATUS "${_msg}")
if(VTK_BINARY_DIR)
  message(STATUS "${_msg} - no")
else()
  message(STATUS "${_msg} - yes")
endif()

# Display build properties
set(_msg "VTKWikiExamples: Setting executables prefix")
message(STATUS "${_msg}")
if(VTK_BINARY_DIR)
  set(WIKI "wiki")
  message(STATUS "${_msg} - yes [prefix: ${WIKI}]")
else()
  set(WIKI "")
  message(STATUS "${_msg} - no")
endif()

# Display VTK version
if(NOT VTK_BINARY_DIR)
  find_package(VTK REQUIRED)
endif()
if(NOT VTK_RENDERING_BACKEND)
  set(VTK_RENDERING_BACKEND OpenGL) # Support VTK version prior to introduction of rendering backend
endif()
message(STATUS "VTKWikiExamples: VTK VERSION: ${VTK_VERSION}(${VTK_RENDERING_BACKEND})")

if(Module_WikiExamples)
  #
  # This is a VTK remote module build
  #

  vtk_module_impl()
  if(NOT EXISTS "${VTK_BINARY_DIR}/VTKConfig.cmake")
    return()
  endif()

  find_package(VTK PATHS ${VTK_BINARY_DIR})
  include(${VTK_USE_FILE})
else()
  #
  # This is a stand-alone build
  #

  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
endif()

set(CMAKE_MODULE_PATH ${WikiExamples_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

#-----------------------------------------------------------------------------
include(WikiOutputDirectories)
include(WikiPlatformSpecificChecks)
include(WikiPolicies)
include(WikiTestingConfig)

#-----------------------------------------------------------------------------
# Mac specific
IF(APPLE)
  SET(EXECUTABLE_FLAG MACOSX_BUNDLE)
ENDIF(APPLE)

#-----------------------------------------------------------------------------
ADD_SUBDIRECTORY(src/Cxx/Animation)
ADD_SUBDIRECTORY(src/Cxx/CompositeData)
IF(VTK_USE_MYSQL)
  ADD_SUBDIRECTORY(src/Cxx/Databases)
ENDIF(VTK_USE_MYSQL)
ADD_SUBDIRECTORY(src/Cxx/DataStructures)
if(${VTK_VERSION} VERSION_GREATER "6.10")
  ADD_SUBDIRECTORY(src/Cxx/Developers)
endif()
ADD_SUBDIRECTORY(src/Cxx/Filtering)
ADD_SUBDIRECTORY(src/Cxx/GeometricObjects)
IF(VTK_USE_INFOVIS)
  IF(VTK_USE_BOOST)
    ADD_SUBDIRECTORY(src/Cxx/Graphs)
  ENDIF(VTK_USE_BOOST)
ENDIF(VTK_USE_INFOVIS)
ADD_SUBDIRECTORY(src/Cxx/ImageData)
  ADD_SUBDIRECTORY(src/Cxx/Geovis)
ADD_SUBDIRECTORY(src/Cxx/HyperTreeGrid)
ADD_SUBDIRECTORY(src/Cxx/Images)
ADD_SUBDIRECTORY(src/Cxx/ImplicitFunctions)
ADD_SUBDIRECTORY(src/Cxx/InfoVis)
ADD_SUBDIRECTORY(src/Cxx/Interaction)
ADD_SUBDIRECTORY(src/Cxx/IO)
ADD_SUBDIRECTORY(src/Cxx/Lighting)
ADD_SUBDIRECTORY(src/Cxx/Math)
ADD_SUBDIRECTORY(src/Cxx/Medical)
ADD_SUBDIRECTORY(src/Cxx/Meshes)
ADD_SUBDIRECTORY(src/Cxx/Modelling)
IF(VTK_USE_PARALLEL)
  ADD_SUBDIRECTORY(src/Cxx/Parallel)
ENDIF(VTK_USE_PARALLEL)
ADD_SUBDIRECTORY(src/Cxx/Picking)
ADD_SUBDIRECTORY(src/Cxx/Plotting)
ADD_SUBDIRECTORY(src/Cxx/PolyData)
ADD_SUBDIRECTORY(src/Cxx/Points)
ADD_SUBDIRECTORY(src/Cxx/RectilinearGrid)
ADD_SUBDIRECTORY(src/Cxx/Remote)
ADD_SUBDIRECTORY(src/Cxx/Rendering)
ADD_SUBDIRECTORY(src/Cxx/RenderMan)
ADD_SUBDIRECTORY(src/Cxx/SimpleOperations)
ADD_SUBDIRECTORY(src/Cxx/StructuredGrid)
ADD_SUBDIRECTORY(src/Cxx/StructuredPoints)
ADD_SUBDIRECTORY(src/Cxx/Texture)
ADD_SUBDIRECTORY(src/Cxx/UnstructuredGrid)
ADD_SUBDIRECTORY(src/Cxx/Utilities)
ADD_SUBDIRECTORY(src/Cxx/Video)
IF(VTK_USE_VIEWS)
  ADD_SUBDIRECTORY(src/Cxx/Views)
ENDIF(VTK_USE_VIEWS)
ADD_SUBDIRECTORY(src/Cxx/Visualization)
ADD_SUBDIRECTORY(src/Cxx/VisualizationAlgorithms)
ADD_SUBDIRECTORY(src/Cxx/VolumeRendering)
ADD_SUBDIRECTORY(src/Cxx/Widgets)

# ADD_SUBDIRECTORY(Python/GeometricObjects)

if(vtkGUISupportQt_LOADED)
  message(STATUS "VTKWikiExamples: Building Qt examples")
  if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
    # We have ui files, this will bring in the macro: qt5_wrap_ui
    find_package(Qt5Widgets REQUIRED QUIET)
  else()
    FIND_PACKAGE(Qt4 REQUIRED)
    INCLUDE(${QT_USE_FILE})
  endif()
  ADD_SUBDIRECTORY(src/Cxx/Qt)
else()
  message(STATUS "VTKWikiExamples: Not building Qt examples")
endif()
