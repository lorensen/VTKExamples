[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/TextureMapImageData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestTextureMapImageData.png?raw=true" width="256" />

### Description
This example creates an image and texture maps it onto a plane.

**TextureMapImageData.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkImageCanvasSource2D.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTexture.h>

int main(int, char *[])
{
  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetExtent(0, 20, 0, 20, 0, 0);
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetDrawColor(127,255,100);
  imageSource->FillBox(0,20,0,20);
  imageSource->SetDrawColor(20,20,20);
  imageSource->DrawSegment(0, 0, 19, 19);
  imageSource->DrawSegment(19, 0, 0, 19);
  imageSource->Update();
  
  // Create a plane
  vtkSmartPointer<vtkPlaneSource> plane = 
    vtkSmartPointer<vtkPlaneSource>::New();
  plane->SetCenter(0.0, 0.0, 0.0);
  plane->SetNormal(0.0, 0.0, 1.0);
  
  // Apply the texture
  vtkSmartPointer<vtkTexture> texture = 
    vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(imageSource->GetOutputPort());

  vtkSmartPointer<vtkPolyDataMapper> planeMapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  planeMapper->SetInputConnection(plane->GetOutputPort());

  vtkSmartPointer<vtkActor> texturedPlane = 
    vtkSmartPointer<vtkActor>::New();
  texturedPlane->SetMapper(planeMapper);
  texturedPlane->SetTexture(texture);

  // Visualize the textured plane
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(texturedPlane);
  renderer->SetBackground(1,1,1); // Background color white
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
 
PROJECT(TextureMapImageData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(TextureMapImageData MACOSX_BUNDLE TextureMapImageData.cxx)
 
target_link_libraries(TextureMapImageData ${VTK_LIBRARIES})
```

**Download and Build TextureMapImageData**

Click [here to download TextureMapImageData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/TextureMapImageData.tar) and its *CMakeLists.txt* file.
Once the *tarball TextureMapImageData.tar* has been downloaded and extracted,
```
cd TextureMapImageData/build 
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
./TextureMapImageData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

