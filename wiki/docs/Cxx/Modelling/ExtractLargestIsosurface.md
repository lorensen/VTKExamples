[VTKExamples](/index/)/[Cxx](/Cxx)/Modelling/ExtractLargestIsosurface

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Modelling/TestExtractLargestIsosurface.png?raw=true" width="256" />

### Description
* Contributed by: Jinyoung Hwang

This example reads a structured points dataset stored in a .vtk file and constructs a 3D model using vtkMarchingCubes.
vtkPolyDataConnectivityFilter is used to extract the largest isosurface.

Data is available at:
 1. test.vtk: http://web.kaist.ac.kr/~hjy/test.vtk
 2. brainweb.img: http://web.kaist.ac.kr/~hjy/brainweb.img
 3. brainweb.hdr: http://web.kaist.ac.kr/~hjy/brainweb.hdr
Second and third datasets can be downloaded from BrainWeb (http://www.bic.mni.mcgill.ca/brainweb/), which is free of charge in use for a research.
"test.vtk" was converted from "brainweb.img" using a program by Erik Vidholm (http://www.cb.uu.se/~erik/vtk/rawToVTK.cpp).

The examples expects 2 or 3 argments:

 ExtractLargestIsosurface InputFilename Threshold [](ExtractLargest)
  if ExtractLargest is omitted or 1, the largest isosurface is extracted
  if ExtractLargest is 0, all of the isosurfaces are extracted

Try
 ExtractLargestIsosurface test.vtk 50 1
and compare the results to
 ExtractLargestIsosurface test.vtk 50 0

**ExtractLargestIsosurface.cxx**
```c++
#include "vtkSmartPointer.h"
#include "vtkStructuredPointsReader.h"
#include "vtkMarchingCubes.h"
#include "vtkPolyDataConnectivityFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0]
              << " InputFile(.vtk) Threshold" << std::endl;
    return EXIT_FAILURE;
  }
  const char* fileName = argv[1];
  float threshold = atof(argv[2]);
  int extractLargest = 1;
  if (argc == 4)
  {
    extractLargest = atoi(argv[3]);
  }

  // Load data
  vtkSmartPointer<vtkStructuredPointsReader> reader =
    vtkSmartPointer<vtkStructuredPointsReader>::New();
  reader->SetFileName(fileName);

  // Create a 3D model using marching cubes
  vtkSmartPointer<vtkMarchingCubes> mc =
    vtkSmartPointer<vtkMarchingCubes>::New();
  mc->SetInputConnection(reader->GetOutputPort());
  mc->ComputeNormalsOn();
  mc->ComputeGradientsOn();
  mc->SetValue(0, threshold);  // second value acts as threshold

  // To remain largest region
  vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter =
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
  confilter->SetInputConnection(mc->GetOutputPort());
  confilter->SetExtractionModeToLargestRegion();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  if (extractLargest)
  {
    mapper->SetInputConnection(confilter->GetOutputPort());
  }
  else
  {
    mapper->SetInputConnection(mc->GetOutputPort());
  }

  mapper->ScalarVisibilityOff();    // utilize actor's property I set

  // Visualize
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->GetProperty()->SetColor(1,1,1);
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);

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
 
PROJECT(ExtractLargestIsosurface)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractLargestIsosurface MACOSX_BUNDLE ExtractLargestIsosurface.cxx)
 
target_link_libraries(ExtractLargestIsosurface ${VTK_LIBRARIES})
```

**Download and Build ExtractLargestIsosurface**

Click [here to download ExtractLargestIsosurface](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractLargestIsosurface.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractLargestIsosurface.tar* has been downloaded and extracted,
```
cd ExtractLargestIsosurface/build 
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
./ExtractLargestIsosurface
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

