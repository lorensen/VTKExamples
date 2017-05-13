[VTKExamples](/home/)/[Cxx](/Cxx)/Visualization/DepthSortPolyData

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Visualization/TestDepthSortPolyData.png?raw=true" width="256" />

### Description

* Contributed by: Lars Friedrich

This is a C++-port of the VTK example '''DepthSort.py''' found in
[VTKSourceDir/Examples/VisualizationAlgorithms/Python(https://gitlab.kitware.com/vtk/vtk/blob/master/Examples/VisualizationAlgorithms/Python/DepthSort.py). It
was slightly modified. It generates 5 spheres with configurable PHI
and THETA resolution. The spheres overlap. Therefore, correct blending
and visualization in general requires depth sorting of the underlying
polygons which will not happen when simply using a poly data
mapper. Depth sorting can be achieved by connecting a
*vtkDepthSortPolyData* filter to the mapper instead of the pure poly
data.

### Program Usage

*Usage: ./DepthSortPolyData DepthSortFlag ThetaResolution  PhiResolution ScalarVisibilityFlag*

DepthSortFlag ... activate/deactivate the depth sorting algorithm

ThetaResolution ... THETA resolution for the spheres

PhiResolution ... PHI resolution for the spheres

ScalarVisibilityFlag ... show/hide the found depth values as scalars

*Example calls:*

./DepthSortPolyData 0 100 100 0
... will render the spheres 'as usual' (without depth sorting); in general you will be confronted with situations (specific view directions) where you cannot determine whether a small sphere is behind or in front of the big center sphere

./DepthSortPolyData 1 100 100 0
... will render the spheres using depth sorting; the sphere depth order should now be visually traceable

./DepthSortPolyData 1 100 100 1
... will render the spheres using depth sorting; the depth values are mapped to the spheres and renderd on the surfaces

Using higher PHI/THETA resolutions shows how depth sorting reduces the frame rate.

**DepthSortPolyData.cxx**
```c++
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkAppendPolyData.h>
#include <vtkCamera.h>
#include <vtkDepthSortPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main (int argc, char *argv[])
{
  if (argc != 5)
  {
    std::cerr << "Usage: " << argv[0] << " DepthSortFlag ThetaResolution " <<
      " PhiResolution ScalarVisibilityFlag" << std::endl;
    return EXIT_FAILURE;
  }

  bool doDepthSort = atoi(argv[1]) == 1;
  int theta = atoi(argv[2]);
  int phi = atoi(argv[3]);
  bool scalarVisibility = atoi(argv[4]) == 1;

  // Create a bunch of spheres that overlap and cannot be easily arranged
  // so that the blending works without sorting. They are appended into a
  // single vtkPolyData because the filter only sorts within a single
  // vtkPolyData input.
  vtkSmartPointer<vtkAppendPolyData> appendData =
    vtkSmartPointer<vtkAppendPolyData>::New();

  for (int i = 0; i < 5; i++)
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(theta);
    sphereSource->SetPhiResolution(phi);
    sphereSource->SetRadius(0.5); //all sphere except the center one should have radius = 0.5
    switch (i)
    {
      case 0:
        sphereSource->SetRadius(1);
        sphereSource->SetCenter(0, 0, 0); break;
      case 1:
        sphereSource->SetCenter(1, 0, 0); break;
      case 2:
        sphereSource->SetCenter(-1, 0, 0); break;
      case 3:
        sphereSource->SetCenter(0, 1, 0); break;
      case 4:
        sphereSource->SetCenter(0, -1, 0); break;
    }
    sphereSource->Update();
    appendData->AddInputConnection(sphereSource->GetOutputPort());
  }

  // The dephSort object is set up to generate scalars representing
  // the sort depth.  A camera is assigned for the sorting. The camera
  // defines the sort vector (position and focal point).
  vtkSmartPointer<vtkCamera> camera =
    vtkSmartPointer<vtkCamera>::New();
  vtkSmartPointer<vtkDepthSortPolyData> depthSort =
    vtkSmartPointer<vtkDepthSortPolyData>::New();

  depthSort->SetInputConnection(appendData->GetOutputPort());
  depthSort->SetDirectionToBackToFront();
  depthSort->SetVector(1, 1, 1);
  depthSort->SetCamera(camera);
  depthSort->SortScalarsOn();
  depthSort->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  if (doDepthSort)
  {
    mapper->SetInputConnection(depthSort->GetOutputPort());
  }
  else
  {
    mapper->SetInputConnection(appendData->GetOutputPort());
  }

  mapper->SetScalarVisibility(scalarVisibility);
  if (scalarVisibility)
  {
    mapper->SetScalarRange(0, depthSort->GetOutput()->GetNumberOfCells());
  }

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();

  actor->SetMapper(mapper);
  actor->GetProperty()->SetOpacity(0.5);
  actor->GetProperty()->SetColor(1, 0, 0);
  actor->RotateX(-72); //put the object in a position where it is easy
  // to see different overlapping regions

  // If an Prop3D is supplied, then its transformation matrix is taken
  // into account during sorting.
  depthSort->SetProp3D(actor);

  // Create the RenderWindow, Renderer and both Actors
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetActiveCamera(camera);
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(actor);
  renderer->SetBackground(.1, .2, .31);
  renderWindow->SetSize(600, 400);

  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(2.2); //so the object is larger

  renderWindowInteractor->Initialize();
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DepthSortPolyData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DepthSortPolyData MACOSX_BUNDLE DepthSortPolyData.cxx)
 
target_link_libraries(DepthSortPolyData ${VTK_LIBRARIES})
```

**Download and Build DepthSortPolyData**

Click [here to download DepthSortPolyData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DepthSortPolyData.tar) and its *CMakeLists.txt* file.
Once the *tarball DepthSortPolyData.tar* has been downloaded and extracted,
```
cd DepthSortPolyData/build 
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
./DepthSortPolyData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

