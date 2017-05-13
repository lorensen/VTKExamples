[VTKExamples](/index/)/[Cxx](/Cxx)/Utilities/OffScreenRendering

### Description
This example renders a scene directly to a file without displaying a window. You must turn on VTK_OPENGL_HAS_OSMESA in the VTK advanced build configuration.

**OffScreenRendering.cxx**
```c++
#include <vtkVersion.h>
#if VTK_MAJOR_VERSION >= 6
int main(int, char *argv[])
{
  std::cout << argv[0] << " requires VTK 5.10 or earlier. This VTK version is " << vtkVersion::GetVTKVersion() << std::endl;
  return EXIT_SUCCESS;
}
#else
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkGraphicsFactory.h>
#include <vtkImagingFactory.h>

int main(int, char *[])
{
  // Setup offscreen rendering
  vtkSmartPointer<vtkGraphicsFactory> graphics_factory = 
    vtkSmartPointer<vtkGraphicsFactory>::New();
  graphics_factory->SetOffScreenOnlyMode( 1);
  graphics_factory->SetUseMesaClasses( 1 );
  
  vtkSmartPointer<vtkImagingFactory> imaging_factory = 
    vtkSmartPointer<vtkImagingFactory>::New();
  imaging_factory->SetUseMesaClasses( 1 ); 
  
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
    
  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
  
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->SetOffScreenRendering( 1 ); 
  renderWindow->AddRenderer(renderer);

  // Add the actors to the scene
  renderer->AddActor(actor);
  renderer->SetBackground(1,1,1); // Background color white

  renderWindow->Render();

  vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = 
    vtkSmartPointer<vtkWindowToImageFilter>::New();
  windowToImageFilter->SetInput(renderWindow);
  windowToImageFilter->Update();
  
  vtkSmartPointer<vtkPNGWriter> writer = 
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName("screenshot.png");
  writer->SetInputConnection(windowToImageFilter->GetOutputPort());
  writer->Write();

  return EXIT_SUCCESS;
}
#endif
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OffScreenRendering)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OffScreenRendering MACOSX_BUNDLE OffScreenRendering.cxx)
 
target_link_libraries(OffScreenRendering ${VTK_LIBRARIES})
```

**Download and Build OffScreenRendering**

Click [here to download OffScreenRendering](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OffScreenRendering.tar) and its *CMakeLists.txt* file.
Once the *tarball OffScreenRendering.tar* has been downloaded and extracted,
```
cd OffScreenRendering/build 
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
./OffScreenRendering
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

