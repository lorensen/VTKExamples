#-----------------------------------------------------------------------------
# Set policies as needed.
foreach(p
    CMP0020 # CMake 2.8.11
    CMP0022 # CMake 2.8.12
    CMP0025 # CMake 3.0
    CMP0043 # CMake 3.0
    CMP0053 # CMake 3.1
    CMP0071
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()
#-----------------------------------------------------------------------------

project (QtVTKWikiExamples)

if(NOT VTK_BINARY_DIR)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkChartsCore
    vtkCommonColor
    vtkCommonCore
    vtkCommonDataModel
    vtkFiltersCore
    vtkFiltersSources
    vtkGUISupportQt
    vtkInfovisCore
    vtkInteractionStyle
    vtkInteractionWidgets
    vtkRenderingContext2D
    vtkRenderingContextOpenGL2
    vtkRenderingCore
    vtkRenderingFreeType
    vtkRenderingGL2PSOpenGL2
    vtkRenderingOpenGL2
    vtkRenderingQt
    vtkViewsContext2D
    vtkViewsQt
    QUIET
    )
    if (VTK_VERSION VERSION_LESS "8.90.0")
      include(${VTK_USE_FILE})
    endif()
endif()

set(KIT_LIBS ${VTK_LIBRARIES})

# Let Qt find its MOCed headers in the build directory.
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#
# For all [example].ui files, build them together with their corresponding
# [example]Driver.cxx and [example].cxx. Subtract these cxx files from a
# list of all cxx files in the directory - we will build the rest in the next block.
file(GLOB ALL_UI_FILES *.ui)
file(GLOB ALL_FILES *.cxx)

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
  qt5_wrap_ui(UISrcs ${EXAMPLE}.ui)
  # CMAKE_AUTOMOC in ON so the MocHdrs will be automatically wrapped.
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}Driver.cxx ${EXAMPLE}.cxx ${UISrcs} ${EXAMPLE}.h)
  if (Qt5Widgets_VERSION VERSION_LESS "5.11.0")
    qt5_use_modules(${WIKI}${EXAMPLE} Core Gui Widgets)
  else()
    target_link_libraries(${WIKI}${EXAMPLE} Qt5::Core Qt5::Gui Qt5::Widgets)
  endif()
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  if (VTK_VERSION VERSION_GREATER "8.8")
    vtk_module_autoinit(
      TARGETS ${WIKI}${EXAMPLE}
      MODULES ${VTK_LIBRARIES}
      )
  endif()
  list(REMOVE_ITEM ALL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE}Driver.cxx ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE}.cxx)
endforeach()

# Build all remaining .cxx files.
foreach(EXAMPLE_FILE ${ALL_FILES})
  string(REPLACE ".cxx" "" TMP ${EXAMPLE_FILE})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" EXAMPLE ${TMP})
  add_executable(${WIKI}${EXAMPLE} ${EXECUTABLE_FLAG} ${EXAMPLE}.cxx)
  if (Qt5Widgets_VERSION VERSION_LESS "5.11.0")
    qt5_use_modules(${WIKI}${EXAMPLE} Core Gui Widgets)
  else()
    target_link_libraries(${WIKI}${EXAMPLE} Qt5::Core Qt5::Gui Qt5::Widgets)
  endif()
  target_link_libraries(${WIKI}${EXAMPLE} ${KIT_LIBS})
  if (VTK_VERSION VERSION_GREATER "8.8")
  vtk_module_autoinit(
    TARGETS ${WIKI}${EXAMPLE}
    MODULES ${VTK_LIBRARIES}
    )
  endif()
endforeach()
