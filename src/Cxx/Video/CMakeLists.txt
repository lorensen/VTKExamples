project (${WIKI}Video)

include(${WikiExamples_SOURCE_DIR}/CMake/AddOptionalIfInLibrary.cmake)
if(NOT VTK_BINARY_DIR)
  set(optional "")
  Add_Optional_If_In_Library(vtkIOFFMPEG VTK_LIBRARIES optional)
  Add_Optional_If_In_Library(vtkIOOggTheora VTK_LIBRARIES optional)
  set(VTK_LIBRARIES "")
  find_package(VTK COMPONENTS
    vtkCommonCore
    vtkImagingSources
    ${optional}
    QUIET
    )
  if (VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()
endif()

if(WIN32)
  if(VTK_USE_VIDEO_FOR_WINDOWS)
    set(KIT_LIBS ${KIT_LIBS} vfw32)
  endif()
endif()
Requires_Setting_On(AVI VTK_USE_VIDEO_FOR_WINDOWS)
Requires_Setting_On(MPEG2 VTK_USE_MPEG2_ENCODER)
Requires_Setting_On(FFMPEG VTK_USE_FFMPEG2_ENCODER)
Requires_Setting_On(OggTheora VTK_USE_OGGTHEORA_ENCODER)
