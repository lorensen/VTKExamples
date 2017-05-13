[VTKExamples](/home/)/[Cxx](/Cxx)/Modelling/MarchingSquares

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Modelling/TestMarchingSquares.png?raw=true" width="256" />

**MarchingSquares.cxx**
```c++
#include "vtkMarchingSquares.h"
#include "vtkSmartPointer.h"

#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPNGReader.h"
#include "vtkDataSetMapper.h"
#include "vtkCamera.h"
#include "vtkProperty.h"

int main(int argc, char* argv[])
{
  std::string inputFileName;
  if (argc > 1 )
  {
    inputFileName = argv[1];
  }
  int isoValue = 500;
  if (argc > 2)
  {
    isoValue = atoi(argv[2]);
  }

  vtkSmartPointer<vtkPNGReader> reader =
    vtkSmartPointer<vtkPNGReader>::New();
  if (!reader->CanReadFile(inputFileName.c_str()))
  {
    std::cerr << "Error: Could not read " << inputFileName << ".\n";
    return EXIT_FAILURE;
  }
  reader->SetFileName(inputFileName.c_str());
  reader->Update();

  vtkSmartPointer<vtkMarchingSquares> iso =
    vtkSmartPointer<vtkMarchingSquares>::New();
  iso->SetInputConnection(reader->GetOutputPort());
  iso->SetValue(0, isoValue);

  vtkSmartPointer<vtkDataSetMapper> isoMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  isoMapper->SetInputConnection(iso->GetOutputPort());
  isoMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> isoActor =
    vtkSmartPointer<vtkActor>::New();
  isoActor->SetMapper(isoMapper);
  isoActor->GetProperty()->SetColor(0.8900, 0.8100, 0.3400);

  // Standard rendering classes
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->SetMultiSamples(0);
  renWin->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(isoActor);

  // Standard testing code.
  renderer->SetBackground(0.5,0.5,0.5);
  renWin->SetSize(300,300);

  vtkCamera *camera = renderer->GetActiveCamera();
  renderer->ResetCamera();
  camera->Azimuth(180);

  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MarchingSquares)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MarchingSquares MACOSX_BUNDLE MarchingSquares.cxx)
 
target_link_libraries(MarchingSquares ${VTK_LIBRARIES})
```

**Download and Build MarchingSquares**

Click [here to download MarchingSquares](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MarchingSquares.tar) and its *CMakeLists.txt* file.
Once the *tarball MarchingSquares.tar* has been downloaded and extracted,
```
cd MarchingSquares/build 
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
./MarchingSquares
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

