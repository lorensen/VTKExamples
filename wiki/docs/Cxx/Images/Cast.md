[VTKExamples](/home/)/[Cxx](/Cxx)/Images/Cast

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestCast.png?raw=true" width="256" />

### Description
Cast an image to a different type.

**Cast.cxx**
```c++
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageCast.h>
#include <vtkImageMapper3D.h>
#include <vtkImageActor.h>
#include <vtkImageMandelbrotSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleImage.h>

int main(int, char *[])
{
  // Create a float image
  vtkSmartPointer<vtkImageMandelbrotSource> source =
    vtkSmartPointer<vtkImageMandelbrotSource>::New();
  source->Update();

  std::cout << source->GetOutput()->GetScalarTypeAsString() << std::endl;

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
 
PROJECT(Cast)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Cast MACOSX_BUNDLE Cast.cxx)
 
target_link_libraries(Cast ${VTK_LIBRARIES})
```

**Download and Build Cast**

Click [here to download Cast](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Cast.tar) and its *CMakeLists.txt* file.
Once the *tarball Cast.tar* has been downloaded and extracted,
```
cd Cast/build 
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
./Cast
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

