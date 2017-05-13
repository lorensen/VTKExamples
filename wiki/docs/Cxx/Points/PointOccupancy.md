[VTKExamples](/home/)/[Cxx](/Cxx)/Points/PointOccupancy

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Points/TestPointOccupancy.png?raw=true" width="256" />

### Description
'''NOTE: The classes used in this example require vtk 7.1 or later.'''

**PointOccupancy.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPointSource.h>
#include <vtkPLYReader.h>
#include <vtkSTLReader.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkOBJReader.h>

#include <vtkPointOccupancyFilter.h>
#include <vtkThreshold.h>
#include <vtkDataSetMapper.h>
#include <vtkImageData.h>

#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

#include <vtksys/SystemTools.hxx>

static vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName);

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> polyData = ReadPolyData(argc > 1 ? argv[1] : "");;
  int dimension = 128;
  vtkSmartPointer<vtkPointOccupancyFilter> occupancy = 
    vtkSmartPointer<vtkPointOccupancyFilter>::New();
  occupancy->SetInputData(polyData);
  occupancy->SetSampleDimensions(dimension, dimension, dimension);
  occupancy->SetOccupiedValue(255);
  occupancy->Update();

  vtkSmartPointer<vtkThreshold> threshold =
    vtkSmartPointer<vtkThreshold>::New();
  threshold->SetInputConnection(occupancy->GetOutputPort());
  threshold->ThresholdByUpper(255);
  threshold->AllScalarsOff();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(threshold->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Colors
  vtkSmartPointer<vtkNamedColors> nc =
    vtkSmartPointer<vtkNamedColors>::New();
  double flesh[3];
  nc->GetColorRGB("moccasin", flesh);
  actor->GetProperty()->SetColor(flesh);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);
  
  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(actor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.25);
  ren1->ResetCameraClippingRange();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}

static vtkSmartPointer<vtkPolyData> ReadPolyData(const char *fileName)
{
  vtkSmartPointer<vtkPolyData> polyData;
  std::string extension = vtksys::SystemTools::GetFilenameExtension(std::string(fileName));
  if (extension == ".ply")
  {
    vtkSmartPointer<vtkPLYReader> reader =
      vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".vtp")
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".obj")
  {
    vtkSmartPointer<vtkOBJReader> reader =
      vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else if (extension == ".stl")
  {
    vtkSmartPointer<vtkSTLReader> reader =
      vtkSmartPointer<vtkSTLReader>::New();
    reader->SetFileName (fileName);
    reader->Update();
    polyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkPointSource> points =
      vtkSmartPointer<vtkPointSource>::New();
    points->SetNumberOfPoints(1000);
    points->SetRadius(10.0);
    points->SetCenter(vtkMath::Random(-100, 100),
                      vtkMath::Random(-100, 100),
                      vtkMath::Random(-100, 100));
    points->SetDistributionToShell();
    points->Update();
    polyData = points->GetOutput();
  }
  return polyData;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PointOccupancy)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PointOccupancy MACOSX_BUNDLE PointOccupancy.cxx)
 
target_link_libraries(PointOccupancy ${VTK_LIBRARIES})
```

**Download and Build PointOccupancy**

Click [here to download PointOccupancy](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PointOccupancy.tar) and its *CMakeLists.txt* file.
Once the *tarball PointOccupancy.tar* has been downloaded and extracted,
```
cd PointOccupancy/build 
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
./PointOccupancy
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

