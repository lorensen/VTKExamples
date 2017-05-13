[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/ShepardMethod

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Utilities/TestShepardMethod.png?raw=true" width="256" />

### Description
This example samples unstructured points onto structured points using the Shepard method. The example starts with two points which have associated scalars (0 (black) and 1(white)). The results are displayed by coloring planes between the two points with the corresponding interpolated values. The values are reflected by black (0) to white (1).

**ShepardMethod.cxx**
```c++
#include <vtkVersion.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkColorTransferFunction.h>
#include <vtkContourFilter.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkShepardMethod.h>
#include <vtkSmartPointer.h>
#include <vtkVertexGlyphFilter.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  // Create a set of vertices (polydata)
  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(100.0, 0.0, 0.0);
  points->InsertNextPoint(300.0, 0.0, 0.0);

  // Setup colors
  unsigned char white[3] = {255, 255, 255};
  unsigned char black[3] = {0, 0, 0};

  vtkSmartPointer<vtkUnsignedCharArray> vertexColors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  vertexColors->SetNumberOfComponents(3);
  vertexColors->SetName("Colors");
  vertexColors->InsertNextTupleValue(black);
  vertexColors->InsertNextTupleValue(white);

  // Create a scalar array for the pointdata, each value represents the distance
  // of the vertices from the first vertex
  vtkSmartPointer<vtkFloatArray> values =
      vtkSmartPointer<vtkFloatArray>::New();
  values->SetNumberOfComponents(1);
  values->SetName("Values");
  values->InsertNextValue(0.0);
  values->InsertNextValue(1.0);

  // We must make two objects, because the ShepardMethod uses the ActiveScalars, as does the renderer!
  vtkSmartPointer<vtkPolyData> polydataToProcess =
      vtkSmartPointer<vtkPolyData>::New();
  polydataToProcess->SetPoints(points);
  polydataToProcess->GetPointData()->SetScalars(values);

  vtkSmartPointer<vtkPolyData> polydataToVisualize =
    vtkSmartPointer<vtkPolyData>::New();
  polydataToVisualize->SetPoints(points);
  polydataToVisualize->GetPointData()->SetScalars(vertexColors);

  vtkSmartPointer<vtkVertexGlyphFilter> vertexGlyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexGlyphFilter->AddInputConnection(polydataToVisualize->GetProducerPort());
#else
  vertexGlyphFilter->AddInputData(polydataToVisualize);
#endif
  vertexGlyphFilter->Update();

  //Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> vertsMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  //vertsMapper->ScalarVisibilityOff();
  vertsMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> vertsActor =
    vtkSmartPointer<vtkActor>::New();
  vertsActor->SetMapper(vertsMapper);
  vertsActor->GetProperty()->SetColor(1,0,0);
  vertsActor->GetProperty()->SetPointSize(3);

  // Create a shepard filter to interpolate the vertices over a regularized image grid
  vtkSmartPointer<vtkShepardMethod> shepard = vtkSmartPointer<vtkShepardMethod>::New();
#if VTK_MAJOR_VERSION <= 5
  shepard->SetInputConnection(polydataToProcess->GetProducerPort());
#else
  shepard->SetInputData(polydataToProcess);
#endif
  shepard->SetSampleDimensions(2,2,2);
  shepard->SetModelBounds(100,300,-10,10,-10,10);
  shepard->SetMaximumDistance(1);

  // Contour the shepard generated image at 3 isovalues
  // The accuracy of the results are highly dependent on how the shepard filter is set up
  vtkSmartPointer<vtkContourFilter> contourFilter = vtkSmartPointer<vtkContourFilter>::New();
  contourFilter->SetNumberOfContours(3);
  contourFilter->SetValue(0, 0.25);
  contourFilter->SetValue(1, 0.50);
  contourFilter->SetValue(2, 0.75);
  contourFilter->SetInputConnection(shepard->GetOutputPort());
  contourFilter->Update();

  //Create a mapper and actor for the resulting isosurfaces
  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contourFilter->GetOutputPort());
  contourMapper->ScalarVisibilityOn();
  contourMapper->SetColorModeToMapScalars();

  vtkSmartPointer<vtkActor> contourActor =
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);
  contourActor->GetProperty()->SetAmbient(1);
  contourActor->GetProperty()->SetSpecular(0);
  contourActor->GetProperty()->SetDiffuse(0);

  // Report the results of the interpolation
  double *range = contourFilter->GetOutput()->GetScalarRange();

  std::cout << "Shepard interpolation:" << std::endl;
  std::cout << "contour output scalar range: " << range[0] << ", " << range[1] << std::endl;

  vtkIdType nCells = contourFilter->GetOutput()->GetNumberOfCells();
  double bounds[6];
  for( vtkIdType i = 0; i < nCells; ++i )
  {
    if(i%2) // each isosurface value only has 2 cells to report on the odd ones
    {
      contourFilter->GetOutput()->GetCellBounds(i,bounds);
      std::cout << "cell " << i << ", x position: " << bounds[0] << std::endl;
    }
  }

  // Create a transfer function to color the isosurfaces
  vtkSmartPointer<vtkColorTransferFunction> lut =
    vtkSmartPointer<vtkColorTransferFunction>::New();
  lut->SetColorSpaceToRGB();
  lut->AddRGBPoint(range[0],0,0,0);//black
  lut->AddRGBPoint(range[1],1,1,1);//white
  lut->SetScaleToLinear();

  contourMapper->SetLookupTable( lut );

  // Create a renderer, render window and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->GradientBackgroundOn();
  renderer->SetBackground(0,0,1);
  renderer->SetBackground2(1,0,1);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(contourActor);
  renderer->AddActor(vertsActor);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Position the camera so that the image produced is viewable
  vtkCamera* camera = renderer->GetActiveCamera();
  camera->SetPosition(450, 100, 100);
  camera->SetFocalPoint(200, 0, 0);
  camera->SetViewUp(0, 0, 1);

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ShepardMethod)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ShepardMethod MACOSX_BUNDLE ShepardMethod.cxx)
 
target_link_libraries(ShepardMethod ${VTK_LIBRARIES})
```

**Download and Build ShepardMethod**

Click [here to download ShepardMethod](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ShepardMethod.tar) and its *CMakeLists.txt* file.
Once the *tarball ShepardMethod.tar* has been downloaded and extracted,
```
cd ShepardMethod/build 
```
If VTK is installed:
```
cmake ..
```
If VTK is not installed but compiled on your system, you will need to specify the path to your VTK build:
```
cmake -DVTK_DIR:PATH=/home/me/vtk_build ..
```
Build the project:
```
make
```
and run it:
```
./ShepardMethod
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

