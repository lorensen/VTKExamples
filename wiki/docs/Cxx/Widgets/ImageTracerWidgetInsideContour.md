[VTKExamples](Home)/[Cxx](Cxx)/Widgets/ImageTracerWidgetInsideContour

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Widgets/TestImageTracerWidgetInsideContour.png" width="256" />

**ImageTracerWidgetInsideContour.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkImageData.h>
#include <vtkCallbackCommand.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkImageTracerWidget.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkInteractorStyleImage.h>
#include <vtkProperty.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkImageStencilToImage.h>
#include <vtkPNGWriter.h>
#include <vtkImageAccumulate.h>

namespace
{
void CallbackFunction (vtkObject* caller, long unsigned int eventId,
                        void* clientData, void* callData );

void CreateImage1(vtkImageData*);

}

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> image =
    vtkSmartPointer<vtkImageData>::New();
  CreateImage1(image);

  vtkSmartPointer<vtkImageActor> actor =
    vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
  actor->GetMapper()->SetInput(image);
#else
  actor->GetMapper()->SetInputData(image);
#endif

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
  tracer->AutoCloseOn();
  renderWindow->Render();

  // The observer must be added BEFORE the On() call.
  vtkSmartPointer<vtkCallbackCommand> callback =
    vtkSmartPointer<vtkCallbackCommand>::New();
  callback->SetCallback(CallbackFunction);
  callback->SetClientData(image);
  tracer->AddObserver(vtkCommand::EndInteractionEvent, callback);

  tracer->On();
  interactor->Start();

  return EXIT_SUCCESS;
}

namespace
{
void CallbackFunction (vtkObject* caller,
                       long unsigned int vtkNotUsed(eventId),
                       void* clientData,
                       void* vtkNotUsed(callData) )
{
  vtkImageTracerWidget* tracerWidget =
    static_cast<vtkImageTracerWidget*>(caller);

  vtkSmartPointer<vtkPolyData> path =
    vtkSmartPointer<vtkPolyData>::New();

  if(!tracerWidget->IsClosed())
  {
    std::cout << "Path not closed!" << std::endl;
    return;
  }

  tracerWidget->GetPath(path);
  std::cout << "There are " << path->GetNumberOfPoints() << " points in the path." << std::endl;

  vtkImageData* image =
    static_cast<vtkImageData*>(clientData);

  vtkSmartPointer<vtkPolyDataToImageStencil> polyDataToImageStencil =
    vtkSmartPointer<vtkPolyDataToImageStencil>::New();
  polyDataToImageStencil->SetTolerance(0);
#if VTK_MAJOR_VERSION <= 5
  polyDataToImageStencil->SetInputConnection(path->GetProducerPort());
#else
  polyDataToImageStencil->SetInputData(path);
#endif
  polyDataToImageStencil->SetOutputOrigin(image->GetOrigin());
  polyDataToImageStencil->SetOutputSpacing(image->GetSpacing());
  polyDataToImageStencil->SetOutputWholeExtent(image->GetExtent());
  polyDataToImageStencil->Update();

  vtkSmartPointer<vtkImageStencilToImage> imageStencilToImage =
    vtkSmartPointer<vtkImageStencilToImage>::New();
  imageStencilToImage->SetInputConnection(polyDataToImageStencil->GetOutputPort());
  imageStencilToImage->SetInsideValue(255);
  imageStencilToImage->Update();

  vtkSmartPointer<vtkImageAccumulate> imageAccumulate =
    vtkSmartPointer<vtkImageAccumulate>::New();
#if VTK_MAJOR_VERSION <= 5
  imageAccumulate->SetStencil(polyDataToImageStencil->GetOutput());
  imageAccumulate->SetInputConnection(image->GetProducerPort());
#else
  imageAccumulate->SetStencilData(polyDataToImageStencil->GetOutput());
  imageAccumulate->SetInputData(image);
#endif
  imageAccumulate->Update();
  std::cout << "Voxel count: " << imageAccumulate->GetVoxelCount() << std::endl;

  vtkSmartPointer<vtkPNGWriter> writer =
    vtkSmartPointer<vtkPNGWriter>::New();
  writer->SetFileName("selection.png");
  writer->SetInputConnection(imageStencilToImage->GetOutputPort());
  writer->Write();
}


void CreateImage1(vtkImageData* image)
{
  vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
    vtkSmartPointer<vtkImageCanvasSource2D>::New();
  imageSource->SetScalarTypeToUnsignedChar();
  imageSource->SetNumberOfScalarComponents(1);
  imageSource->SetExtent(0, 20, 0, 50, 0, 0);
  imageSource->SetDrawColor(255,255,255);
  imageSource->FillBox(0,20,0,50);
  imageSource->Update();

  image->ShallowCopy(imageSource->GetOutput());

}
} // end anonymous namespace
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageTracerWidgetInsideContour)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImageTracerWidgetInsideContour MACOSX_BUNDLE ImageTracerWidgetInsideContour.cxx)
 
target_link_libraries(ImageTracerWidgetInsideContour ${VTK_LIBRARIES})
```

**Download and Build ImageTracerWidgetInsideContour**

Click [here to download ImageTracerWidgetInsideContour](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImageTracerWidgetInsideContour.tar) and its *CMakeLists.txt* file.
Once the *tarball ImageTracerWidgetInsideContour.tar* has been downloaded and extracted,
```
cd ImageTracerWidgetInsideContour/build 
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
./ImageTracerWidgetInsideContour
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

