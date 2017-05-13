[VTKExamples](Home)/[Cxx](Cxx)/ImplicitFunctions/IsoContours

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/ImplicitFunctions/TestIsoContours.png" width="256" />

**IsoContours.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleUser.h>
#include <vtkProperty.h>
#include <vtkOutlineFilter.h>
#include <vtkCommand.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation.h>
#include <vtkSliderRepresentation3D.h>
#include <vtkImageData.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include <vtkXMLImageDataWriter.h>

static void CreateData(vtkImageData* data);

class vtkSliderCallback : public vtkCommand
{
public:
  static vtkSliderCallback *New()
  {
    return new vtkSliderCallback;
  }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkSliderWidget *sliderWidget =
      reinterpret_cast<vtkSliderWidget*>(caller);
    double value = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
    this->ContourFilter->GenerateValues(1, value, value);

  }
  vtkSliderCallback():ContourFilter(NULL) {}
  vtkContourFilter* ContourFilter;
};

int main(int, char *[])
{
  vtkSmartPointer<vtkImageData> data =
    vtkSmartPointer<vtkImageData>::New();
  CreateData(data);

  // Create an isosurface
  vtkSmartPointer<vtkContourFilter> contourFilter =
    vtkSmartPointer<vtkContourFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  contourFilter->SetInput(data);
#else
  contourFilter->SetInputData(data);
#endif
  contourFilter->GenerateValues(1, 10, 10); // (numContours, rangeStart, rangeEnd)

  // Map the contours to graphical primitives
  vtkSmartPointer<vtkPolyDataMapper> contourMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  contourMapper->SetInputConnection(contourFilter->GetOutputPort());

  // Create an actor for the contours
  vtkSmartPointer<vtkActor> contourActor =
    vtkSmartPointer<vtkActor>::New();
  contourActor->SetMapper(contourMapper);

  // Create the outline
  vtkSmartPointer<vtkOutlineFilter> outlineFilter =
    vtkSmartPointer<vtkOutlineFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  outlineFilter->SetInput(data);
#else
  outlineFilter->SetInputData(data);
#endif
  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());
  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);

  // Visualize
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  renderer->AddActor(contourActor);
  renderer->AddActor(outlineActor);

  vtkSmartPointer<vtkSliderRepresentation3D> sliderRep =
    vtkSmartPointer<vtkSliderRepresentation3D>::New();
  sliderRep->SetMinimumValue(0.0);
  sliderRep->SetMaximumValue(30.0);
  sliderRep->SetValue(10.0);
  sliderRep->SetTitleText("Contour value");
  sliderRep->SetPoint1InWorldCoordinates(-20, -40, 0);
  sliderRep->SetPoint2InWorldCoordinates(0, -40, 0);
  sliderRep->SetSliderWidth(.2);
  sliderRep->SetLabelHeight(.1);

  vtkSmartPointer<vtkSliderWidget> sliderWidget =
    vtkSmartPointer<vtkSliderWidget>::New();
  sliderWidget->SetInteractor(interactor);
  sliderWidget->SetRepresentation(sliderRep);
  sliderWidget->SetAnimationModeToAnimate();
  sliderWidget->EnabledOn();

  vtkSmartPointer<vtkSliderCallback> callback =
    vtkSmartPointer<vtkSliderCallback>::New();
  callback->ContourFilter = contourFilter;

  sliderWidget->AddObserver(vtkCommand::InteractionEvent,callback);

  vtkSmartPointer<vtkInteractorStyleUser> style =
    vtkSmartPointer<vtkInteractorStyleUser>::New();
  interactor->SetInteractorStyle(style);

  renderWindow->SetSize(500,500);
  renderWindow->Render();
  renderWindow->Render();
  interactor->Start();

  return EXIT_SUCCESS;
}

void CreateData(vtkImageData* data)
{
  data->SetExtent(-25,25,-25,25,0,0);
#if VTK_MAJOR_VERSION <= 5
  data->SetNumberOfScalarComponents(1);
  data->SetScalarTypeToDouble();
#else
  data->AllocateScalars(VTK_DOUBLE,1);
#endif
  int* extent = data->GetExtent();

  for (int y = extent[2]; y <= extent[3]; y++)
  {
    for (int x = extent[0]; x <= extent[1]; x++)
    {
      double* pixel = static_cast<double*>(data->GetScalarPointer(x,y,0));
      pixel[0] = sqrt(pow(x,2.0) + pow(y,2.0));
    }
  }

  vtkSmartPointer<vtkXMLImageDataWriter> writer =
    vtkSmartPointer<vtkXMLImageDataWriter>::New();
  writer->SetFileName("data.vti");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInputConnection(data->GetProducerPort());
#else
  writer->SetInputData(data);
#endif
  writer->Write();
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(IsoContours)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(IsoContours MACOSX_BUNDLE IsoContours.cxx)
 
target_link_libraries(IsoContours ${VTK_LIBRARIES})
```

**Download and Build IsoContours**

Click [here to download IsoContours](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/IsoContours.tar) and its *CMakeLists.txt* file.
Once the *tarball IsoContours.tar* has been downloaded and extracted,
```
cd IsoContours/build 
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
./IsoContours
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

