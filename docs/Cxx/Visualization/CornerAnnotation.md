[VTKExamples](/index/)/[Cxx](/Cxx)/Visualization/CornerAnnotation

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestCornerAnnotation.png?raw=true" width="256" />

**CornerAnnotation.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTextProperty.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCornerAnnotation.h>

int main( int, char *[] )
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
      vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();
  
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
      vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( sphereSource->GetOutputPort() );
 
  vtkSmartPointer<vtkActor> actor = 
      vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );
  
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer( renderer );
  
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow( renderWindow );
  renderer->AddActor( actor );
  
   // Annotate the image with window/level and mouse over pixel information
  vtkSmartPointer<vtkCornerAnnotation> cornerAnnotation = 
      vtkSmartPointer<vtkCornerAnnotation>::New();
  cornerAnnotation->SetLinearFontScaleFactor( 2 );
  cornerAnnotation->SetNonlinearFontScaleFactor( 1 );
  cornerAnnotation->SetMaximumFontSize( 20 );
  cornerAnnotation->SetText( 0, "lower left" );
  cornerAnnotation->SetText( 1, "lower right" );
  cornerAnnotation->SetText( 2, "upper left" );
  cornerAnnotation->SetText( 3, "upper right" );
  cornerAnnotation->GetTextProperty()->SetColor( 1, 0, 0 );

  renderer->AddViewProp( cornerAnnotation );
  
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CornerAnnotation)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CornerAnnotation MACOSX_BUNDLE CornerAnnotation.cxx)
 
target_link_libraries(CornerAnnotation ${VTK_LIBRARIES})
```

**Download and Build CornerAnnotation**

Click [here to download CornerAnnotation](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CornerAnnotation.tar) and its *CMakeLists.txt* file.
Once the *tarball CornerAnnotation.tar* has been downloaded and extracted,
```
cd CornerAnnotation/build 
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
./CornerAnnotation
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

