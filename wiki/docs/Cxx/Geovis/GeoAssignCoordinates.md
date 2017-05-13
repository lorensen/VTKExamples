[VTKExamples](/index/)/[Cxx](/Cxx)/Geovis/GeoAssignCoordinates

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Geovis/TestGeoAssignCoordinates.png?raw=true" width="256" />

**GeoAssignCoordinates.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkVersion.h>

#include <vtkDataSetAttributes.h>
#include <vtkGeoAssignCoordinates.h>
#include <vtkDoubleArray.h>
#include <vtkGraphMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMutableDirectedGraph.h>

int main(int, char* [])
{

  vtkSmartPointer<vtkMutableDirectedGraph> g =
    vtkSmartPointer<vtkMutableDirectedGraph>::New();

  vtkSmartPointer<vtkDoubleArray> latitude =
    vtkSmartPointer<vtkDoubleArray>::New();
  latitude->SetName("latitude");

  vtkSmartPointer<vtkDoubleArray> longitude =
    vtkSmartPointer<vtkDoubleArray>::New();
  longitude->SetName("longitude");

  for(int lat = -90; lat <= 90; lat += 10)
  {
    for(int lon = -180; lon <= 180; lon += 20)
    {
      g->AddVertex();
      latitude->InsertNextValue(lat);
      longitude->InsertNextValue(lon);
    }
  }

  g->GetVertexData()->AddArray(latitude);
  g->GetVertexData()->AddArray(longitude);

  vtkSmartPointer<vtkGeoAssignCoordinates> assign =
    vtkSmartPointer<vtkGeoAssignCoordinates>::New();
#if VTK_MAJOR_VERSION <= 5
  assign->SetInput(g);
#else
  assign->SetInputData(g);
#endif
  assign->SetLatitudeArrayName("latitude");
  assign->SetLongitudeArrayName("longitude");
  assign->SetGlobeRadius(1.0);
  assign->Update();

  vtkSmartPointer<vtkGraphMapper> mapper =
    vtkSmartPointer<vtkGraphMapper>::New();
  mapper->SetInputConnection(assign->GetOutputPort());
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> ren =
    vtkSmartPointer<vtkRenderer>::New();
  ren->AddActor(actor);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<vtkRenderWindow> win =
    vtkSmartPointer<vtkRenderWindow>::New();
  win->AddRenderer(ren);
  win->SetInteractor(iren);
  ren->ResetCamera();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GeoAssignCoordinates)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GeoAssignCoordinates MACOSX_BUNDLE GeoAssignCoordinates.cxx)
 
target_link_libraries(GeoAssignCoordinates ${VTK_LIBRARIES})
```

**Download and Build GeoAssignCoordinates**

Click [here to download GeoAssignCoordinates](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GeoAssignCoordinates.tar) and its *CMakeLists.txt* file.
Once the *tarball GeoAssignCoordinates.tar* has been downloaded and extracted,
```
cd GeoAssignCoordinates/build 
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
./GeoAssignCoordinates
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

