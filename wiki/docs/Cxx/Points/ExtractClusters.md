[VTKExamples](/index/)/[Cxx](/Cxx)/Points/ExtractClusters

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Points/TestExtractClusters.png?raw=true" width="256" />

### Description
This example extracts clusters of points. The points lie on spheres that are randomly placed. Each cluster has a different color. The number of extracted clusters may be less that the number of random spheres, if the points on one sphere are within the specified distance of points on another sphere.
'''NOTE: The classes used in this example require vtk 7.1 or later.'''

**ExtractClusters.cxx**
```c++
#include <vtkSmartPointer.h>

#include <vtkEuclideanClusterExtraction.h>
#include <vtkPointSource.h>
#include <vtkAppendPolyData.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>

#include <vtkLookupTable.h>

#include <vtkMath.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main (int, char *[])
{
  vtkMath::RandomSeed(4355412); // for test result consistency
  double limits = 10;
  double radius = .5;

  vtkSmartPointer<vtkAppendPolyData> append =
    vtkSmartPointer<vtkAppendPolyData>::New();
  for (unsigned i = 0; i < 30; ++i)
  {
    vtkSmartPointer<vtkPointSource> points =
      vtkSmartPointer<vtkPointSource>::New();
    points->SetNumberOfPoints(800);
    points->SetRadius(2.5 * radius);
    points->SetCenter(vtkMath::Random(-limits, limits),
                      vtkMath::Random(-limits, limits),
                      vtkMath::Random(-limits, limits));
    points->SetDistributionToShell();

    append->AddInputConnection(points->GetOutputPort());
  }

  vtkSmartPointer<vtkEuclideanClusterExtraction> cluster =
    vtkSmartPointer<vtkEuclideanClusterExtraction>::New();
  cluster->SetInputConnection(append->GetOutputPort());
  cluster->SetExtractionModeToAllClusters();
  cluster->SetRadius(radius);
  cluster->ColorClustersOn();
  cluster->Update();

  std::cout << "Found " << cluster->GetNumberOfExtractedClusters()
            << " clusters within radius " << radius << std::endl;

  // Create a lookup table to map point data to colors
  vtkSmartPointer<vtkLookupTable> lut =
    vtkSmartPointer<vtkLookupTable>::New();
  int tableSize = cluster->GetNumberOfExtractedClusters();
  lut->SetNumberOfTableValues(tableSize);
  lut->Build();

  // Fill in the lookup table
  for (unsigned int i = 0; i < tableSize; ++i)
  {
    lut->SetTableValue(i,
                       vtkMath::Random(.25, 1.0),
                       vtkMath::Random(.25, 1.0),
                       vtkMath::Random(.25, 1.0),
                       1.0);
  }

  vtkSmartPointer<vtkSphereSource> sphere =
    vtkSmartPointer<vtkSphereSource>::New();
  sphere->SetRadius(radius / 2.0);

  vtkSmartPointer<vtkGlyph3D> glyphs =
    vtkSmartPointer<vtkGlyph3D>::New();
  glyphs->SetInputConnection(cluster->GetOutputPort());
  glyphs->SetSourceConnection(sphere->GetOutputPort());
  glyphs->ScalingOff();
  glyphs->Update();

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(glyphs->GetOutputPort());
  mapper->SetScalarRange(0, tableSize - 1);
  mapper->SetLookupTable(lut);

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.3, .4, .6);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(640, 512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer
  //
  ren1->AddActor(actor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.5);
  ren1->ResetCameraClippingRange();

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractClusters)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractClusters MACOSX_BUNDLE ExtractClusters.cxx)
 
target_link_libraries(ExtractClusters ${VTK_LIBRARIES})
```

**Download and Build ExtractClusters**

Click [here to download ExtractClusters](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractClusters.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractClusters.tar* has been downloaded and extracted,
```
cd ExtractClusters/build 
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
./ExtractClusters
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

