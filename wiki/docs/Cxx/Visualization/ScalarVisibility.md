[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/ScalarVisibility

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestScalarVisibility.png?raw=true" width="256" />

**ScalarVisibility.cxx**
```c++
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkPointSource.h"
#include "vtkProperty.h"
#include "vtkPolyData.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource = vtkSmartPointer<vtkPointSource>::New();
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(pointSource->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );
  unsigned char red[3] = {255, 0, 0};
  actor->GetProperty()->SetColor(red[0], red[1], red[2]);
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow( renderWindow );

  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ScalarVisibility)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ScalarVisibility MACOSX_BUNDLE ScalarVisibility.cxx)
 
target_link_libraries(ScalarVisibility ${VTK_LIBRARIES})
```

**Download and Build ScalarVisibility**

Click [here to download ScalarVisibility](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ScalarVisibility.tar) and its *CMakeLists.txt* file.
Once the *tarball ScalarVisibility.tar* has been downloaded and extracted,
```
cd ScalarVisibility/build 
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
./ScalarVisibility
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

