[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/ProgrammableGlyphFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestProgrammableGlyphFilter.png?raw=true" width="256" />

**ProgrammableGlyphFilter.cxx**
```c++
#include <vtkVersion.h>

#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkCubeSource.h>
#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkProgrammableGlyphFilter.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkFloatArray.h>

void CalcGlyph(void *arg)
{

  vtkProgrammableGlyphFilter *glyphFilter = (vtkProgrammableGlyphFilter*) arg;

  if(!glyphFilter)
  {
    std::cerr << "glyphFilter is not valid!" << std::endl;
  }
  double pointCoords[3];
  glyphFilter->GetPoint(pointCoords);

  std::cout << "Calling CalcGlyph for point "
            << glyphFilter->GetPointId() << std::endl;
  std::cout << "Point coords are: "
            << pointCoords[0] << " "
            << pointCoords[1] << " "
            << pointCoords[2] << std::endl;
  if(glyphFilter->GetPointId() == 0)
  {
    vtkSmartPointer<vtkConeSource> coneSource =
      vtkSmartPointer<vtkConeSource>::New();
    coneSource->SetCenter(pointCoords);
#if VTK_MAJOR_VERSION <= 5
    glyphFilter->SetSource(coneSource->GetOutput());
#else
    glyphFilter->SetSourceConnection(coneSource->GetOutputPort());
#endif
  }
  else if(glyphFilter->GetPointId() == 1)
  {
    vtkSmartPointer<vtkCubeSource> cubeSource =
      vtkSmartPointer<vtkCubeSource>::New();
    cubeSource->SetCenter(pointCoords);
#if VTK_MAJOR_VERSION <= 5
    glyphFilter->SetSource(cubeSource->GetOutput());
#else
    glyphFilter->SetSourceConnection(cubeSource->GetOutputPort());
#endif
  }
  else if(glyphFilter->GetPointId() == 2)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(pointCoords);
#if VTK_MAJOR_VERSION <= 5
    glyphFilter->SetSource(sphereSource->GetOutput());
#else
    glyphFilter->SetSourceConnection(sphereSource->GetOutputPort());
#endif
  }
}

int main(int, char *[])
{
  // Create points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(5,0,0);
  points->InsertNextPoint(10,0,0);

  // Combine into a polydata
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  vtkSmartPointer<vtkProgrammableGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkProgrammableGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInput(polydata);
#else
  glyphFilter->SetInputData(polydata);
#endif
  glyphFilter->SetGlyphMethod(CalcGlyph, glyphFilter);
  //need a default glyph, but this should not be used
  vtkSmartPointer<vtkConeSource> coneSource =
    vtkSmartPointer<vtkConeSource>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetSource(coneSource->GetOutput());
#else
  glyphFilter->SetSourceConnection(coneSource->GetOutputPort());
#endif

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actor to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(.2, .3, .4);

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ProgrammableGlyphFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ProgrammableGlyphFilter MACOSX_BUNDLE ProgrammableGlyphFilter.cxx)
 
target_link_libraries(ProgrammableGlyphFilter ${VTK_LIBRARIES})
```

**Download and Build ProgrammableGlyphFilter**

Click [here to download ProgrammableGlyphFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ProgrammableGlyphFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball ProgrammableGlyphFilter.tar* has been downloaded and extracted,
```
cd ProgrammableGlyphFilter/build 
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
./ProgrammableGlyphFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

