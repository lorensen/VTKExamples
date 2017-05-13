[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/VisualizeImageData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestVisualizeImageData.png?raw=true" width="256" />

**VisualizeImageData.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char*[])
{
  // Create an image data
  vtkSmartPointer<vtkImageData> imageData = 
    vtkSmartPointer<vtkImageData>::New();
  
  // Specify the size of the image data
  imageData->SetDimensions(3,3,2);
  imageData->SetSpacing(1.0, 1.0, 1.0);
  imageData->SetOrigin(0.0, 0.0, 0.0);
  
  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(imageData->GetProducerPort());
#else
  mapper->SetInputData(imageData);
#endif
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  
  // Add both renderers to the window
  renderWindow->AddRenderer(renderer);
      
  // Add a sphere to the left and a cube to the right
  renderer->AddActor(actor);
  
  renderer->ResetCamera();
  
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
 
PROJECT(VisualizeImageData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VisualizeImageData MACOSX_BUNDLE VisualizeImageData.cxx)
 
target_link_libraries(VisualizeImageData ${VTK_LIBRARIES})
```

**Download and Build VisualizeImageData**

Click [here to download VisualizeImageData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VisualizeImageData.tar) and its *CMakeLists.txt* file.
Once the *tarball VisualizeImageData.tar* has been downloaded and extracted,
```
cd VisualizeImageData/build 
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
./VisualizeImageData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

