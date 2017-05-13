[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/PolygonalSurfacePointPlacer

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestPolygonalSurfacePointPlacer.png?raw=true" width="256" />

### Description
This example demonstrates how to draw curves on a surface.

**PolygonalSurfacePointPlacer.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkProperty.h>
#include <vtkContourWidget.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataCollection.h>
#include <vtkPolygonalSurfacePointPlacer.h>
#include <vtkOrientedGlyphContourRepresentation.h>

class MyCallback : public vtkCommand
{
  public:
    static MyCallback *New()
    {
      return new MyCallback;
    }
    MyCallback(){}
    
    virtual void Execute(vtkObject *caller, unsigned long, void*)
    {
      vtkContourWidget *contourWidget = reinterpret_cast<vtkContourWidget*>(caller);
      vtkContourRepresentation* rep = static_cast<vtkContourRepresentation *>(contourWidget->GetRepresentation());
      std::cout << "There are " << rep->GetNumberOfNodes() << " nodes." << std::endl;
    }
    
  void SetSphereSource(vtkSmartPointer<vtkSphereSource> sphere) {this->SphereSource = sphere;}
  
  private:
    vtkSmartPointer<vtkSphereSource> SphereSource;
};

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetRadius(5);
  sphereSource->Update();
 
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
 
  // Create the RenderWindow, Renderer
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);
 
  renderer->AddActor(actor);
 
  vtkSmartPointer<vtkContourWidget> contourWidget = 
    vtkSmartPointer<vtkContourWidget>::New();
  contourWidget->SetInteractor(interactor);
  
  
  vtkSmartPointer<MyCallback> callback = 
    vtkSmartPointer<MyCallback>::New();
  callback->SetSphereSource(sphereSource);
  contourWidget->AddObserver(vtkCommand::InteractionEvent,callback);
  
  vtkOrientedGlyphContourRepresentation* rep = 
    vtkOrientedGlyphContourRepresentation::SafeDownCast(
    contourWidget->GetRepresentation());

  vtkSmartPointer<vtkPolygonalSurfacePointPlacer> pointPlacer =
    vtkSmartPointer<vtkPolygonalSurfacePointPlacer>::New();
  pointPlacer->AddProp(actor);
  pointPlacer->GetPolys()->AddItem(sphereSource->GetOutput());

  rep->GetLinesProperty()->SetColor(1, 0, 0);
  rep->GetLinesProperty()->SetLineWidth(3.0);
  rep->SetPointPlacer(pointPlacer);
  
  contourWidget->EnabledOn();
  renderer->ResetCamera();
  renderWindow->Render();
  interactor->Initialize();
 
  interactor->Start();
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolygonalSurfacePointPlacer)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolygonalSurfacePointPlacer MACOSX_BUNDLE PolygonalSurfacePointPlacer.cxx)
 
target_link_libraries(PolygonalSurfacePointPlacer ${VTK_LIBRARIES})
```

**Download and Build PolygonalSurfacePointPlacer**

Click [here to download PolygonalSurfacePointPlacer](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolygonalSurfacePointPlacer.tar) and its *CMakeLists.txt* file.
Once the *tarball PolygonalSurfacePointPlacer.tar* has been downloaded and extracted,
```
cd PolygonalSurfacePointPlacer/build 
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
./PolygonalSurfacePointPlacer
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

