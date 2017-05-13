[VTKExamples](/home/)/[Cxx](/Cxx)/Widgets/LogoWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestLogoWidget.png?raw=true" width="256" />

### Description
Turn the widget on before the render. Otherwise, it won't appear until you interact with the scene.

**LogoWidget.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkLogoRepresentation.h>
#include <vtkLogoWidget.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkSphereSource.h>

int main(int, char *[])
{
  // A sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(4.0);
  sphereSource->SetPhiResolution(4);
  sphereSource->SetThetaResolution(8);
  sphereSource->Update();

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
  renderWindow->AddRenderer(renderer);
  renderer->AddActor(actor);
  
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Create an image
  vtkSmartPointer<vtkImageCanvasSource2D> drawing = 
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  drawing->SetScalarTypeToUnsignedChar();
  drawing->SetNumberOfScalarComponents(3);
  drawing->SetExtent(0,200,0,200,0,0);

  // Clear the image
  drawing->SetDrawColor(255, 127, 100);
  drawing->FillBox(0,200,0,200);
  drawing->SetDrawColor(0, 0, 0);
  drawing->DrawCircle(100, 100, 50);
  drawing->Update();

  vtkSmartPointer<vtkLogoRepresentation> logoRepresentation = 
    vtkSmartPointer<vtkLogoRepresentation>::New();
  logoRepresentation->SetImage(drawing->GetOutput());
  logoRepresentation->SetPosition(0,0);
  logoRepresentation->SetPosition2(.4, .4);
  logoRepresentation->GetImageProperty()->SetOpacity(.7);
  
  vtkSmartPointer<vtkLogoWidget> logoWidget = 
    vtkSmartPointer<vtkLogoWidget>::New();
  logoWidget->SetInteractor(renderWindowInteractor);
  logoWidget->SetRepresentation(logoRepresentation);
  
  renderWindow->Render();
  logoWidget->On();
  renderer->SetBackground(.2, .3, .4);
  renderWindow->Render();
  renderWindowInteractor->Start();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(LogoWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(LogoWidget MACOSX_BUNDLE LogoWidget.cxx)
 
target_link_libraries(LogoWidget ${VTK_LIBRARIES})
```

**Download and Build LogoWidget**

Click [here to download LogoWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/LogoWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball LogoWidget.tar* has been downloaded and extracted,
```
cd LogoWidget/build 
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
./LogoWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

