[VTKExamples](/index/)/[Cxx](/Cxx)/Images/DrawShapes

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Images/TestDrawShapes.png?raw=true" width="256" />

**DrawShapes.cxx**
```c++
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageCanvasSource2D.h>

int main(int, char *[])
{
  // Create a blank, black image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0, 20, 0, 50, 0, 0);
  drawing->FillBox(0,20,0,50);

  // Draw a red circle of radius 5 centered at (9,10)
  //drawing->SetDrawColor(255, 0, 0, 0.5);
  drawing->SetDrawColor(255, 0, 0, 0);
  drawing->DrawCircle(9, 10, 5);
  drawing->Update();
  
  // View the result
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkImageViewer2> imageViewer = 
    vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(drawing->GetOutputPort());
  imageViewer->SetupInteractor(renderWindowInteractor);
  imageViewer->GetRenderer()->ResetCamera();
  imageViewer->GetRenderer()->SetBackground(1,1,1); //white background
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DrawShapes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DrawShapes MACOSX_BUNDLE DrawShapes.cxx)
 
target_link_libraries(DrawShapes ${VTK_LIBRARIES})
```

**Download and Build DrawShapes**

Click [here to download DrawShapes](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DrawShapes.tar) and its *CMakeLists.txt* file.
Once the *tarball DrawShapes.tar* has been downloaded and extracted,
```
cd DrawShapes/build 
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
./DrawShapes
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

