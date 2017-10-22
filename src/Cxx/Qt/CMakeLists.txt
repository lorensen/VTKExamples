#-----------------------------------------------------------------------------
# Set policies as needed.
foreach(p
    CMP0020 # CMake 2.8.11
    CMP0022 # CMake 2.8.12
    CMP0025 # CMake 3.0
    CMP0043 # CMake 3.0
    CMP0053 # CMake 3.1
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()
#-----------------------------------------------------------------------------

project (QtVTKWikiExamples)

if(NOT WikiExamples_BINARY_DIR)
find_package(VTK REQUIRED)
if(NOT VTK_USE_RENDERING)
  message(FATAL_ERROR "Example ${PROJECT_NAME} requires VTK_USE_RENDERING.")
endif(NOT VTK_USE_RENDERING)
include(${VTK_USE_FILE})
endif(NOT WikiExamples_BINARY_DIR)

if("${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}" LESS 5.8)
  set(KIT_LIBS vtkHybrid ${QT_LIBRARIES} )
else()
  set(KIT_LIBS ${VTK_LIBRARIES})
endif()

# Let Qt find its MOCed headers in the build directory.
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#
# For all [example].ui files, build them together with their corresponding
# [example]Driver.cxx and [example].cxx. Subtract these cxx files from a
# list of all cxx files in the directory - we will build the rest in the next block.
file(GLOB ALL_UI_FILES *.ui)
file(GLOB ALL_FILES *.cxx)

include(${WikiExamples_SOURCE_DIR}/CMake/RequiresModule.cmake)

Requires_Module(ShareCameraQt vtkViewsQt)
Requires_Module(ShareCameraQtDriver vtkViewsQt)
Requires_Module(SideBySideRenderWindowsQt vtkViewsQt)
Requires_Module(SideBySideRenderWindowsQtDriver vtkViewsQt)
Requires_Module(QImageToImageSource vtkRenderingQt)

foreach(EXAMPLE_FILE ${ALL_UI_FILES})

  string(REPLACE ".ui" "" TMP ${EXAMPLE_FILE})

  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  set(UISrcs)
  set(MOCSrcs)

  if(VTK_QT_VERSION VERSION_GREATER "4")
    qt5_wrap_ui(UISrcs ${EXAMPLE}.ui)
    # CMAKE_AUTOMOC in ON so the MocHdrs will be automatically wrapped.
    add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}Driver.cxx ${EXAMPLE}.cxx ${UISrcs} ${EXAMPLE}.h)
    qt5_use_modules(${WIKI}${EXAMPLE} Core Gui Widgets)
  else()
    add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  endif()
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  list(REMOVE_ITEM ALL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE}Driver.cxx ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE}.cxx)
endforeach(EXAMPLE_FILE)

# Build all remaining .cxx files.
foreach(EXAMPLE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${EXAMPLE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})

  if(VTK_QT_VERSION VERSION_GREATER "4")
    add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
    qt5_use_modules(${WIKI}${EXAMPLE} Core Gui Widgets)
    target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  else()
    add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
    target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  endif()
endforeach(EXAMPLE_FILE)
