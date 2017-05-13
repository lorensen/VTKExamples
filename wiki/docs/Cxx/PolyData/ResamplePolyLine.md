[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/ResamplePolyLine

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestResamplePolyLine.png?raw=true" width="256" />

### Description
This example resamples a polyline with a vtkCardinalSpline. The resampled line will have 10 times the number of points contained in the original polyline. If no XML file is provided, a random polyline is generated.

**ResamplePolyLine.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

#include <vtkXMLPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkMath.h>
#include <vtkSplineFilter.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkCardinalSpline.h>

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData =
    vtkSmartPointer<vtkPolyData>::New();
  if (argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName ( argv[1] );
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkMath::RandomSeed(8775070);
    unsigned int numberOfPoints = 10;
    vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
    for (unsigned int i = 0; i < numberOfPoints; ++i)
    {
      double x = vtkMath::Random(-1, 1);
      double y = vtkMath::Random(-1, 1);
      double z = vtkMath::Random(-1, 1);
      points->InsertNextPoint(x, y, z);
    }
    vtkSmartPointer<vtkCellArray> lines =
      vtkSmartPointer<vtkCellArray>::New();
    lines->InsertNextCell(numberOfPoints);
    for (unsigned int i = 0; i < numberOfPoints; ++i)
    {
      lines->InsertCellPoint(i);
    }
    polyData->SetPoints(points);
    polyData->SetLines(lines);
  }

  vtkSmartPointer<vtkCardinalSpline> spline =
    vtkSmartPointer<vtkCardinalSpline>::New();
  spline->SetLeftConstraint(2);
  spline->SetLeftValue(0.0);
  spline->SetRightConstraint(2);
  spline->SetRightValue(0.0);

  vtkSmartPointer<vtkSplineFilter> splineFilter =
    vtkSmartPointer<vtkSplineFilter>::New();

#if VTK_MAJOR_VERSION <= 5
  splineFilter->SetInput(polyData);
#else
  splineFilter->SetInputData(polyData);
#endif
  splineFilter->SetNumberOfSubdivisions(polyData->GetNumberOfPoints() * 10);
  splineFilter->SetSpline(spline);

  vtkSmartPointer<vtkPolyDataMapper> splineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  splineMapper->SetInputConnection(splineFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> splineActor =
    vtkSmartPointer<vtkActor>::New();
  splineActor->SetMapper(splineMapper);

  vtkSmartPointer<vtkSphereSource> originalNodes =
    vtkSmartPointer<vtkSphereSource>::New();
  originalNodes->SetRadius(.04);
  originalNodes->SetPhiResolution(10);
  originalNodes->SetThetaResolution(10);

  vtkSmartPointer<vtkGlyph3D> glyphOriginal =
    vtkSmartPointer<vtkGlyph3D>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphOriginal->SetInput(polyData);
#else
  glyphOriginal->SetInputData(polyData);
#endif
  glyphOriginal->SetSourceConnection(originalNodes->GetOutputPort());

  vtkSmartPointer<vtkSphereSource> newNodes =
    vtkSmartPointer<vtkSphereSource>::New();
  newNodes->SetRadius(.02);
  newNodes->SetPhiResolution(10);
  newNodes->SetThetaResolution(10);

  vtkSmartPointer<vtkGlyph3D> glyphNew =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyphNew->SetInputConnection(splineFilter->GetOutputPort());
  glyphNew->SetSourceConnection(newNodes->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> originalMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  originalMapper->SetInputConnection(glyphOriginal->GetOutputPort());

  vtkSmartPointer<vtkActor> originalActor =
    vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);
  originalActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);
  originalActor->GetProperty()->SetOpacity(.6);

  vtkSmartPointer<vtkPolyDataMapper> newMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  newMapper->SetInputConnection(glyphNew->GetOutputPort());

  vtkSmartPointer<vtkActor> newActor =
    vtkSmartPointer<vtkActor>::New();
  newActor->SetMapper(newMapper);
  newActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.1, .2, .4);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the scene
  renderer->AddActor(originalActor);
  renderer->AddActor(newActor);
  renderer->AddActor(splineActor);

  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ResamplePolyLine)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ResamplePolyLine MACOSX_BUNDLE ResamplePolyLine.cxx)
 
target_link_libraries(ResamplePolyLine ${VTK_LIBRARIES})
```

**Download and Build ResamplePolyLine**

Click [here to download ResamplePolyLine](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ResamplePolyLine.tar) and its *CMakeLists.txt* file.
Once the *tarball ResamplePolyLine.tar* has been downloaded and extracted,
```
cd ResamplePolyLine/build 
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
./ResamplePolyLine
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

