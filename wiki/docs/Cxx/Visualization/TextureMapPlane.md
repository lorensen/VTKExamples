[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/TextureMapPlane

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestTextureMapPlane.png?raw=true" width="256" />

### Description
This example reads a jpg image file and uses it to texture map a plane.

**TextureMapPlane.cxx**
```c++
#include <vtkImageData.h>
#include <vtkJPEGReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkTextureMapToPlane.h>
#include <vtkPlaneSource.h>
#include <vtkTexture.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main ( int argc, char *argv[] )
{
  // Parse command line arguments
  if ( argc != 2 )
  {
    std::cerr << "Usage: " << argv[0] << " Filename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  // Read the image which will be the texture
  vtkSmartPointer<vtkJPEGReader> jPEGReader =
    vtkSmartPointer<vtkJPEGReader>::New();
  jPEGReader->SetFileName ( inputFilename.c_str() );

  // Create a plane
  vtkSmartPointer<vtkPlaneSource> plane =
    vtkSmartPointer<vtkPlaneSource>::New();
  plane->SetCenter(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);

  // Apply the texture
  vtkSmartPointer<vtkTexture> texture =
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(jPEGReader->GetOutputPort());

  vtkSmartPointer<vtkTextureMapToPlane> texturePlane =
    vtkSmartPointer<vtkTextureMapToPlane>::New();
  texturePlane->SetInputConnection(plane->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> planeMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(texturePlane->GetOutputPort());

  vtkSmartPointer<vtkActor> texturedPlane =
    vtkSmartPointer<vtkActor>::New();
  texturedPlane->SetMapper(planeMapper);
  texturedPlane->SetTexture(texture);

  // Visualize the textured plane
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(texturedPlane);
  renderer->SetBackground(.1, .2, .3); // Background color dark blue
  renderer->ResetCamera();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(TextureMapPlane)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TextureMapPlane MACOSX_BUNDLE TextureMapPlane.cxx)
 
target_link_libraries(TextureMapPlane ${VTK_LIBRARIES})
```

**Download and Build TextureMapPlane**

Click [here to download TextureMapPlane](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TextureMapPlane.tar) and its *CMakeLists.txt* file.
Once the *tarball TextureMapPlane.tar* has been downloaded and extracted,
```
cd TextureMapPlane/build 
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
./TextureMapPlane
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

