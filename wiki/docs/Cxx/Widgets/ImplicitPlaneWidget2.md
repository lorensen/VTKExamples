[VTKExamples](/index/)/[Cxx](/Cxx)/Widgets/ImplicitPlaneWidget2

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Widgets/TestImplicitPlaneWidget2.png?raw=true" width="256" />

### Description
This example shows how to use the second generation ImplicitPlaneWidget2 to interactively define the clipping plane for a polydata. If no arguments are specified, a vtkSphereSource generates the polydata. By specifying a .vtp file, the example can operate on arbitrary polydata.

For example, try VTKData/Data/cow.vtp.

**ImplicitPlaneWidget2.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkXMLPolyDataReader.h>
#include <vtkSphereSource.h>
#include <vtkClipPolyData.h>
#include <vtkPlane.h>

#include <vtkCommand.h>
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

// Callback for the interaction
// This does the actual work: updates the vtkPlane implicit function.
// This in turn causes the pipeline to update and clip the object.
class vtkIPWCallback : public vtkCommand
{
public:
  static vtkIPWCallback *New()
    { return new vtkIPWCallback; }
  virtual void Execute(vtkObject *caller, unsigned long, void*)
  {
    vtkImplicitPlaneWidget2 *planeWidget =
      reinterpret_cast<vtkImplicitPlaneWidget2*>(caller);
    vtkImplicitPlaneRepresentation *rep =
      reinterpret_cast<vtkImplicitPlaneRepresentation*>(planeWidget->GetRepresentation());
    rep->GetPlane(this->Plane);
  }
  vtkIPWCallback():Plane(0),Actor(0) {}
  vtkPlane *Plane;
  vtkActor *Actor;

};

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(10.0);

  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();

  // Setup a visualization pipeline
  vtkSmartPointer<vtkPlane> plane =
    vtkSmartPointer<vtkPlane>::New();
  vtkSmartPointer<vtkClipPolyData> clipper =
    vtkSmartPointer<vtkClipPolyData>::New();
  clipper->SetClipFunction(plane);
  clipper->InsideOutOn();
  if (argc < 2)
  {
    clipper->SetInputConnection(sphereSource->GetOutputPort());
  }
  else
  {
    reader->SetFileName(argv[1]);
    clipper->SetInputConnection(reader->GetOutputPort());
  }

  // Create a mapper and actor
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(clipper->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkProperty> backFaces =
    vtkSmartPointer<vtkProperty>::New();
  backFaces->SetDiffuseColor(.8, .8, .4);

  actor->SetBackfaceProperty(backFaces);

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

  renderWindow->Render();

  // The callback will do the work
  vtkSmartPointer<vtkIPWCallback> myCallback =
    vtkSmartPointer<vtkIPWCallback>::New();
  myCallback->Plane = plane;
  myCallback->Actor = actor;

  vtkSmartPointer<vtkImplicitPlaneRepresentation> rep =
    vtkSmartPointer<vtkImplicitPlaneRepresentation>::New();
  rep->SetPlaceFactor(1.25); // This must be set prior to placing the widget
  rep->PlaceWidget(actor->GetBounds());
  rep->SetNormal(plane->GetNormal());

  vtkSmartPointer<vtkImplicitPlaneWidget2> planeWidget =
    vtkSmartPointer<vtkImplicitPlaneWidget2>::New();
  planeWidget->SetInteractor(renderWindowInteractor);
  planeWidget->SetRepresentation(rep);
  planeWidget->AddObserver(vtkCommand::InteractionEvent,myCallback);

  // Render

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  planeWidget->On();

  // Begin mouse interaction
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImplicitPlaneWidget2)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ImplicitPlaneWidget2 MACOSX_BUNDLE ImplicitPlaneWidget2.cxx)
 
target_link_libraries(ImplicitPlaneWidget2 ${VTK_LIBRARIES})
```

**Download and Build ImplicitPlaneWidget2**

Click [here to download ImplicitPlaneWidget2](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ImplicitPlaneWidget2.tar) and its *CMakeLists.txt* file.
Once the *tarball ImplicitPlaneWidget2.tar* has been downloaded and extracted,
```
cd ImplicitPlaneWidget2/build 
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
./ImplicitPlaneWidget2
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

