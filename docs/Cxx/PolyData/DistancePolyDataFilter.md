[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/DistancePolyDataFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestDistancePolyDataFilter.png?raw=true" width="256" />

### Description
NOTE: This example requires version 5.9.20111206 or higher.

**DistancePolyDataFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkDistancePolyDataFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkScalarBarActor.h>
#include <vtkSphereSource.h>

int main(int argc, char* argv[])
{
  vtkSmartPointer<vtkPolyData> input1;
  vtkSmartPointer<vtkPolyData> input2;
  if (argc == 3)
  {
//     std::cerr << "Usage: " << argv[0]
//               << " filename1.vtk"
//               << " filename2.vtk" << std::endl;
    vtkSmartPointer<vtkPolyDataReader> reader1 =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader1->SetFileName(argv[1]);
    reader1->Update();
    input1 = reader1->GetOutput();

    vtkSmartPointer<vtkPolyDataReader> reader2 =
      vtkSmartPointer<vtkPolyDataReader>::New();
    reader2->SetFileName(argv[2]);
    reader2->Update();
    input2 = reader2->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource1->SetCenter(1, 0, 0);
    sphereSource1->Update();
    input1 = sphereSource1->GetOutput();

    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->Update();
    input2 = sphereSource2->GetOutput();
  }

  vtkSmartPointer<vtkCleanPolyData> clean1 =
    vtkSmartPointer<vtkCleanPolyData>::New();
#if VTK_MAJOR_VERSION <= 5
  clean1->SetInputConnection( input1->GetProducerPort());
#else
  clean1->SetInputData( input1);
#endif

  vtkSmartPointer<vtkCleanPolyData> clean2 =
    vtkSmartPointer<vtkCleanPolyData>::New();
#if VTK_MAJOR_VERSION <= 5
  clean2->SetInputConnection( input2->GetProducerPort());
#else
  clean2->SetInputData( input2);
#endif

  vtkSmartPointer<vtkDistancePolyDataFilter> distanceFilter =
    vtkSmartPointer<vtkDistancePolyDataFilter>::New();

  distanceFilter->SetInputConnection( 0, clean1->GetOutputPort() );
  distanceFilter->SetInputConnection( 1, clean2->GetOutputPort() );
  distanceFilter->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection( distanceFilter->GetOutputPort() );
  mapper->SetScalarRange(
    distanceFilter->GetOutput()->GetPointData()->GetScalars()->GetRange()[0],
    distanceFilter->GetOutput()->GetPointData()->GetScalars()->GetRange()[1]);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper( mapper );

  vtkSmartPointer<vtkScalarBarActor> scalarBar =
    vtkSmartPointer<vtkScalarBarActor>::New();
  scalarBar->SetLookupTable(mapper->GetLookupTable());
  scalarBar->SetTitle("Distance");
  scalarBar->SetNumberOfLabels(4);
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer( renderer );

  vtkSmartPointer<vtkRenderWindowInteractor> renWinInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renWinInteractor->SetRenderWindow( renWin );

  renderer->AddActor( actor );
  renderer->AddActor2D(scalarBar);

  renWin->Render();
  renWinInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DistancePolyDataFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DistancePolyDataFilter MACOSX_BUNDLE DistancePolyDataFilter.cxx)
 
target_link_libraries(DistancePolyDataFilter ${VTK_LIBRARIES})
```

**Download and Build DistancePolyDataFilter**

Click [here to download DistancePolyDataFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DistancePolyDataFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball DistancePolyDataFilter.tar* has been downloaded and extracted,
```
cd DistancePolyDataFilter/build 
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
./DistancePolyDataFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

