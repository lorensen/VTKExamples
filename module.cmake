set(DOCUMENTATION "A collection of examples illustrating how to use VTK")

set(qt_modules "")
if (Module_vtkGUISupportQtOpenGL)
  set(qt_modules vtkRenderingQt vtkViewsQt vtkGUISupportQtOpenGL)
endif()

vtk_module( WikiExamples
  DEPENDS
  vtkFiltersFlowPaths
  vtkFiltersGeneric
  vtkFiltersGeometry
  vtkFiltersParallelStatistics
  vtkFiltersPoints
  vtkFiltersProgrammable
  vtkFiltersSelection
  vtkFiltersTexture
  vtkFiltersVerdict
  vtkIOExodus
  vtkIOExport
  vtkIOImport
  vtkIOInfovis
  vtkIOLSDyna
  vtkIOPLY
  vtkIOParallel
  vtkIOParallelXML
  vtkImagingMath
  vtkImagingMorphological
  vtkImagingStatistics
  vtkImagingStencil
  vtkInteractionImage
  vtkRenderingContext${VTK_RENDERING_BACKEND}
  vtkRenderingImage
  vtkRenderingLOD
  vtkRenderingVolume${VTK_RENDERING_BACKEND}
  vtkRendering${VTK_RENDERING_BACKEND}
  vtkTestingGenericBridge
  vtkTestingRendering
  vtkViewsContext2D
  vtkViewsGeovis
  ${qt_modules}
  DESCRIPTION
    "${DOCUMENTATION}"
)
