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

if(${Powercrust_LOADED})
  list(APPEND DEPENDS
    Powercrust
  )
endif()

if(${SplineDrivenImageSlicer_LOADED})
  list(APPEND DEPENDS
    SplineDrivenImageSlicer
  )
endif()

if(${PoissonReconstruction_LOADED})
  list(APPEND DEPENDS
    PoissonReconstruction
  )
endif()

if(Module_vtkGUISupportQtOpenGL)
  list(APPEND DEPENDS
    vtkGUISupportQtOpenGL
    vtkRenderingQt
    vtkViewsQt
    )
endif()

vtk_module( WikiExamples
  DEPENDS
    ${DEPENDS}
  DESCRIPTION
    "${DOCUMENTATION}"
)
