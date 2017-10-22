set(DOCUMENTATION "A collection of examples illustrating how to use VTK")

set(DEPENDS
  vtkChartsCore
  vtkCommonColor
  vtkCommonComputationalGeometry
  vtkCommonSystem
  vtkFiltersExtraction
  vtkFiltersFlowPaths
  vtkFiltersGeneric
  vtkFiltersGeometry
  vtkFiltersHybrid
  vtkFiltersModeling
  # vtkFiltersParallelStatistics #  Optional
  vtkFiltersPoints
  vtkFiltersProgrammable
  vtkFiltersTexture
  vtkFiltersVerdict
  vtkGeovisCore
  vtkIOExodus
  vtkIOExport
  # vtkIOFFMPEG # Optional
  vtkIOImport
  vtkIOInfovis
  # vtkIOMySQL # Optional
  vtkIOPLY
  vtkIOParallel
  vtkIOParallelXML
  vtkImagingColor
  vtkImagingFourier
  vtkImagingHybrid
  vtkImagingMath
  vtkImagingMorphological
  vtkImagingSources
  vtkImagingStatistics
  vtkImagingStencil
  # vtkInfovisBoostGraphAlgorithms # Optional
  vtkInfovisLayout
  vtkInteractionImage
  vtkRenderingAnnotation
  vtkRenderingContext${VTK_RENDERING_BACKEND}
  vtkRenderingImage
  vtkRenderingLOD
  vtkRenderingLabel
  vtkRendering${VTK_RENDERING_BACKEND}
  vtkRenderingVolume${VTK_RENDERING_BACKEND}
  vtkTestingGenericBridge
  vtkTestingRendering
  vtkViewsContext2D
  vtkViewsInfovis
  )

set(WikiExamples_OPTIONAL_DEPENDS
  PoissonReconstruction
  Powercrust
  SplineDrivenImageSlicer
  vtkFiltersParallelStatistics
  vtkGUISupportQtOpenGL
  vtkInfovisBoostGraphAlgorithms
  vtkIOFFMPEG
  vtkIOMySQL
  vtkRenderingQt
  vtkViewsQt
  )

if(${VTK_VERSION} VERSION_LESS "8.1")
  foreach(optional_dep IN LISTS WikiExamples_OPTIONAL_DEPENDS)
    if(TARGET ${optional_dep} OR ${optional_dep}_LOADED OR Module_${optional_dep})
      list(APPEND DEPENDS
        ${optional_dep}
        )
    endif()
  endforeach()
endif()

vtk_module( WikiExamples
  DEPENDS
    ${DEPENDS}
  DESCRIPTION
    "${DOCUMENTATION}"
)
