[VTKExamples](/home/)/[Cxx](/Cxx)/Widgets/ImageTracerWidget

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestImageTracerWidget.png?raw=true" width="256" />

**ImageTracerWidget.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCallbackCommand.h>
#include <vtkImageActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkImageTracerWidget.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkProperty.h>

namespace
{
void CallbackFunction (vtkObject* caller, long unsigned int eventId,
                        void* clientData, void* callData );
}

int main(int, char *[])
{
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetNumberOfScalarComponents(3);
  imageSource->SetExtent(0, 20, 0, 50, 0, 0);
  imageSource->SetDrawColor(0,0,0);
  imageSource->FillBox(0,20,0,50);
  imageSource->SetDrawColor(255,0,0);
  imageSource->FillBox(0,10,0,30);
  imageSource->Update();

  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
  actor->GetMapper()->SetInputConnection(imageSource->GetOutputPort());

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->ResetCamera();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleImage> style =
    vtkSmartPointer<vtkInteractorStyleImage>::New();
  interactor->SetInteractorStyle(style);

  vtkSmartPointer<vtkImageTracerWidget> tracer =
    vtkSmartPointer<vtkImageTracerWidget>::New();
  tracer->GetLineProperty()->SetLineWidth(5);
  tracer->SetInteractor(interactor);
  tracer->SetViewProp(actor);
  renderWindow->Render();

  // The observer must be added BEFORE the On() call.
  vtkSmartPointer<vtkCallbackCommand> callback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  callback->SetCallback(CallbackFunction);
  tracer->AddObserver(vtkCommand::EndInteractionEvent, callback);
  
  tracer->On();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
void CallbackFunction (vtkObject* caller,
                       long unsigned int vtkNotUsed(eventId),
                       void* vtkNotUsed(clientData),
                       void* vtkNotUsed(callData) )
{
  vtkImageTracerWidget* tracerWidget =
    static_cast<vtkImageTracerWidget*>(caller);

  vtkSmartPointer<vtkPolyData> path =
    vtkSmartPointer<vtkPolyData>::New();

  tracerWidget->GetPath(path);
  std::cout << "There are " << path->GetNumberOfPoints() << " points in the path." << std::endl;
}
} // end anonymous namespace
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageTracerWidget)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageTracerWidget MACOSX_BUNDLE ImageTracerWidget.cxx)
 
target_link_libraries(ImageTracerWidget ${VTK_LIBRARIES})
```

**Download and Build ImageTracerWidget**

Click [here to download ImageTracerWidget](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageTracerWidget.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageTracerWidget.tar* has been downloaded and extracted,
```
cd ImageTracerWidget/build 
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
./ImageTracerWidget
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

