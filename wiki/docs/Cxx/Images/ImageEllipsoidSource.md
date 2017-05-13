[VTKExamples](/home/)/[Cxx](/Cxx)/Images/ImageEllipsoidSource

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestImageEllipsoidSource.png?raw=true" width="256" />

**ImageEllipsoidSource.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageEllipsoidSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkImageCast.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageEllipsoidSource> source = 
    vtkSmartPointer<vtkImageEllipsoidSource>::New();
  source->SetWholeExtent(0, 20, 0, 20, 0, 0);
  source->SetCenter(10,10,0);
  source->SetRadius(3,4,5);
  source->Update();

  vtkSmartPointer<vtkImageCast> castFilter =
    vtkSmartPointer<vtkImageCast>::New();
  castFilter->SetInputConnection(source->GetOutputPort());
  castFilter->SetOutputScalarTypeToUnsignedChar();
  castFilter->Update();

  // Create an actor
  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(castFilter->GetOutputPort());

  // Setup renderer
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();

  // Setup render window
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  // Setup render window interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();

  renderWindowInteractor->SetInteractorStyle(style);

  // Render and start interaction
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindowInteractor->Initialize();

  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageEllipsoidSource)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageEllipsoidSource MACOSX_BUNDLE ImageEllipsoidSource.cxx)
 
target_link_libraries(ImageEllipsoidSource ${VTK_LIBRARIES})
```

**Download and Build ImageEllipsoidSource**

Click [here to download ImageEllipsoidSource](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageEllipsoidSource.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageEllipsoidSource.tar* has been downloaded and extracted,
```
cd ImageEllipsoidSource/build 
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
./ImageEllipsoidSource
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

