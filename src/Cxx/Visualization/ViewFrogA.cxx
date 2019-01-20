#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkImageThreshold.h>
#include <vtkLookupTable.h>
#include <vtkMarchingCubes.h>
#include <vtkMetaImageReader.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkStripper.h>
#include <vtkWindowedSincPolyDataFilter.h>

#include "ViewFrog.cxx"
