[VTKExamples](/index/)/[Cxx](/Cxx)/Meshes/ExtractEdges

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestExtractEdges.png?raw=true" width="256" />

### Description
This example shows how to extract the edges from a PolyData. In this case, we convert a sphere into a wireframe sphere. We demonstrate how to traverse the resulting edges.

**ExtractEdges.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkExtractEdges.h>
#include <vtkSphereSource.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLine.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  std::cout << "Sphere" << endl << "----------" << endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfCells() << " cells." << std::endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfPoints() << " points." << std::endl;

  vtkSmartPointer<vtkExtractEdges> extractEdges =
    vtkSmartPointer<vtkExtractEdges>::New();
  extractEdges->SetInputConnection(sphereSource->GetOutputPort());
  extractEdges->Update();

  vtkCellArray* lines= extractEdges->GetOutput()->GetLines();
  vtkPoints* points = extractEdges->GetOutput()->GetPoints();

  std::cout << std::endl << "Edges" << endl << "----------" << std::endl;
  std::cout << "There are " << lines->GetNumberOfCells() << " cells." << std::endl;
  std::cout << "There are " << points->GetNumberOfPoints() << " points." << std::endl;

  // Traverse all of the edges
  for(vtkIdType i = 0; i < extractEdges->GetOutput()->GetNumberOfCells(); i++)
  {
    //std::cout << "Type: " << extractEdges->GetOutput()->GetCell(i)->GetClassName() << std::endl;
    vtkSmartPointer<vtkLine> line = vtkLine::SafeDownCast(extractEdges->GetOutput()->GetCell(i));
    std::cout << "Line " << i << " : " << *line << std::endl;
  }

  // Visualize the edges

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(extractEdges->GetOutputPort());
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
  renderer->SetBackground(1,1,1); // Background color white

  // Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractEdges)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractEdges MACOSX_BUNDLE ExtractEdges.cxx)
 
target_link_libraries(ExtractEdges ${VTK_LIBRARIES})
```

**Download and Build ExtractEdges**

Click [here to download ExtractEdges](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractEdges.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractEdges.tar* has been downloaded and extracted,
```
cd ExtractEdges/build 
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
./ExtractEdges
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

