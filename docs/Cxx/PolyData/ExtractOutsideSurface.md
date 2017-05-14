[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ExtractOutsideSurface

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/PolyData/TestExtractOutsideSurface.png?raw=true" width="256" />

### Description
This example extracts the outer surface of a multiple surface polydata model. The examples assumes the outside surface is closed and there is only one outside surface. It also assumes that the center of the model lies inside the outer surface.

The example casts a ray from outside the bounds of the model into the center of the model. It uses a vtkCellLocator to intersect the ray with the model. The intersected cell is used as a seed to the vtkPolyDataConnectivityFilter which is run with the extraction mode set to CellSeededRegions.

If run without arguments, the example generates a small (in area) sphere inside a large (in area) sphere. The inner sphere has more cells than the outer sphere, but should not be extracted.

You can try your own surface by specifying a XML PolyData file (.vtp) on the command line.

**ExtractOutsideSurface.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAppendPolyData.h>
#include <vtkCellLocator.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkTriangleFilter.h>

int main(int argc, char *argv[])
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
    // Small sphere with most polgons
    vtkSmartPointer<vtkSphereSource> sphereSource1 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource1->SetThetaResolution(10);
    sphereSource1->SetPhiResolution(10);
    sphereSource1->SetCenter(5, 5, 5);

    // Large sphere with least polygons
    vtkSmartPointer<vtkSphereSource> sphereSource2 =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource2->SetRadius(10);
    sphereSource2->SetCenter(10,1,10);

    vtkSmartPointer<vtkAppendPolyData> appendFilter =
      vtkSmartPointer<vtkAppendPolyData>::New();
    appendFilter->AddInputConnection(sphereSource1->GetOutputPort());
    appendFilter->AddInputConnection(sphereSource2->GetOutputPort());
    appendFilter->Update();
    polyData = appendFilter->GetOutput();
  }

  double center[3], bounds[6];
  polyData->GetCenter(center);
  std::cout << "Center of data is: "
            << center[0] << ", "
            << center[1] << ", "
            << center[2] << std::endl;
  polyData->GetPoints()->GetBounds(bounds);
  std::cout << "Bounds of data is: "
            << bounds[0] << ", "
            << bounds[1] << ", "
            << bounds[2] << ", "
            << bounds[3] << ", "
            << bounds[4] << ", "
            << bounds[5] << std::endl;

  // Build a cell locator.
  vtkSmartPointer<vtkCellLocator> cellLocator =
    vtkSmartPointer<vtkCellLocator>::New();
  cellLocator->SetDataSet(polyData);
  cellLocator->BuildLocator();

  // Now fire a ray from outside the bounds to the center and find a
  // cell. This cell should be on the outside surface
  double rayStart[3];
  for (unsigned int i = 0; i < 3; i++)
  {
    rayStart[i] = bounds[2 * i + 1] * 1.1;
  }

  vtkIdType cellId = -1;
  double xyz[3], t, pcoords[3];
  int subId;

  cellLocator->IntersectWithLine(
    rayStart,
    center,
    0.0001,
    t,
    xyz,
    pcoords,
    subId,
    cellId);
  std::cout << "Id of cell on outside surface: " << cellId << std::endl;

  vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
      vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  connectivityFilter->SetInput(polyData);
#else
  connectivityFilter->SetInputData(polyData);
#endif
  connectivityFilter->SetExtractionModeToCellSeededRegions();
  connectivityFilter->InitializeSeedList();
  connectivityFilter->AddSeed(cellId);

  // Create a mapper and actor for original data
    vtkSmartPointer<vtkPolyDataMapper> originalMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  originalMapper->SetInput(polyData);
#else
  originalMapper->SetInputData(polyData);
#endif

  vtkSmartPointer<vtkActor> originalActor =
      vtkSmartPointer<vtkActor>::New();
  originalActor->SetMapper(originalMapper);

  // Create a mapper and actor for extracted data
  vtkSmartPointer<vtkPolyDataMapper> extractedMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  extractedMapper->SetInputConnection(connectivityFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> extractedActor =
      vtkSmartPointer<vtkActor>::New();
  extractedActor->GetProperty()->SetColor(1,0,0);
  extractedActor->SetMapper(extractedMapper);

  // Create a renderer
  vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(originalActor);
  renderer->AddActor(extractedActor);

  // Create a render window
  vtkSmartPointer<vtkRenderWindow> renwin =
      vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);

  // Create an interactor
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractOutsideSurface)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractOutsideSurface MACOSX_BUNDLE ExtractOutsideSurface.cxx)
 
target_link_libraries(ExtractOutsideSurface ${VTK_LIBRARIES})
```

**Download and Build ExtractOutsideSurface**

Click [here to download ExtractOutsideSurface](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractOutsideSurface.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractOutsideSurface.tar* has been downloaded and extracted,
```
cd ExtractOutsideSurface/build 
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
./ExtractOutsideSurface
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

