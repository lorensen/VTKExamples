[VTKExamples](/index/)/[Cxx](/Cxx)/Meshes/CapClip

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestCapClip.png?raw=true" width="256" />

### Description
This example shows how to generate a "cap" on a clipped polydata. It uses a clever ''trick'' to convert polylines into polygons. If a polydata file (.vtp) is provided, it will cap it. Otherwise it caps a clipped sphere.

**CapClip.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyData.h>
#include <vtkStripper.h>
#include <vtkFeatureEdges.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkClipPolyData.h>
#include <vtkPlane.h>
#include <vtkXMLPolyDataReader.h>

#include <vtkSphereSource.h>

//
// Demonstrate the use of clipping and capping on polyhedral data
//

int main (int argc, char *argv[])
{
  // PolyData to process
  vtkSmartPointer<vtkPolyData> polyData;

  if (argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    // Create a sphere
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(20);
    sphereSource->SetPhiResolution(11);

    vtkSmartPointer<vtkPlane> plane =
      vtkSmartPointer<vtkPlane>::New();
    plane->SetOrigin(0,0,0);
    plane->SetNormal(1.0, -1.0, -1.0);

    vtkSmartPointer<vtkClipPolyData> clipper =
      vtkSmartPointer<vtkClipPolyData>::New();
    clipper->SetInputConnection(sphereSource->GetOutputPort());
    clipper->SetClipFunction(plane);
    clipper->SetValue(0);
    clipper->Update();

    polyData = clipper->GetOutput();
  }

  vtkSmartPointer<vtkDataSetMapper> clipMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  clipMapper->SetInput(polyData);
#else
  clipMapper->SetInputData(polyData);
#endif

  vtkSmartPointer<vtkActor> clipActor =
    vtkSmartPointer<vtkActor>::New();
  clipActor->SetMapper(clipMapper);
  clipActor->GetProperty()->SetColor(1.0000,0.3882,0.2784);
  clipActor->GetProperty()->SetInterpolationToFlat();

  // Now extract feature edges
  vtkSmartPointer<vtkFeatureEdges> boundaryEdges =
    vtkSmartPointer<vtkFeatureEdges>::New();
#if VTK_MAJOR_VERSION <= 5
  boundaryEdges->SetInput(polyData);
#else
  boundaryEdges->SetInputData(polyData);
#endif
  boundaryEdges->BoundaryEdgesOn();
  boundaryEdges->FeatureEdgesOff();
  boundaryEdges->NonManifoldEdgesOff();
  boundaryEdges->ManifoldEdgesOff();

  vtkSmartPointer<vtkStripper> boundaryStrips =
    vtkSmartPointer<vtkStripper>::New();
  boundaryStrips->SetInputConnection(boundaryEdges->GetOutputPort());
  boundaryStrips->Update();

  // Change the polylines into polygons
  vtkSmartPointer<vtkPolyData> boundaryPoly =
    vtkSmartPointer<vtkPolyData>::New();
  boundaryPoly->SetPoints(boundaryStrips->GetOutput()->GetPoints());
  boundaryPoly->SetPolys(boundaryStrips->GetOutput()->GetLines());

  vtkSmartPointer<vtkPolyDataMapper> boundaryMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  boundaryMapper->SetInput(boundaryPoly);
#else
  boundaryMapper->SetInputData(boundaryPoly);
#endif

  vtkSmartPointer<vtkActor> boundaryActor =
    vtkSmartPointer<vtkActor>::New();
  boundaryActor->SetMapper(boundaryMapper);
  boundaryActor->GetProperty()->SetColor(0.8900,0.8100,0.3400);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.1, .2, .3);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(clipActor);
  ren1->AddActor(boundaryActor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(30);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.2);
  ren1->ResetCameraClippingRange();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CapClip)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CapClip MACOSX_BUNDLE CapClip.cxx)
 
target_link_libraries(CapClip ${VTK_LIBRARIES})
```

**Download and Build CapClip**

Click [here to download CapClip](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CapClip.tar) and its *CMakeLists.txt* file.
Once the *tarball CapClip.tar* has been downloaded and extracted,
```
cd CapClip/build 
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
./CapClip
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

