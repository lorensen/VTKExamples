[VTKExamples](Home)/[Cxx](Cxx)/Modelling/ContourTriangulator

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Modelling/TestContourTriangulator.png" width="256" />

**ContourTriangulator.cxx**
```c++
#include "vtkSmartPointer.h"
#include "vtkContourTriangulator.h"
#include "vtkMarchingSquares.h"

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

  vtkSmartPointer<vtkContourTriangulator> poly =
    vtkSmartPointer<vtkContourTriangulator>::New();
  poly->SetInputConnection(iso->GetOutputPort());

  vtkSmartPointer<vtkDataSetMapper> polyMapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  polyMapper->SetInputConnection(poly->GetOutputPort());
  polyMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> polyActor =
    vtkSmartPointer<vtkActor>::New();
  polyActor->SetMapper(polyMapper);
  polyActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);

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

  renderer->AddActor(polyActor);
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
 
PROJECT(ContourTriangulator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ContourTriangulator MACOSX_BUNDLE ContourTriangulator.cxx)
 
target_link_libraries(ContourTriangulator ${VTK_LIBRARIES})
```

**Download and Build ContourTriangulator**

Click [here to download ContourTriangulator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ContourTriangulator.tar) and its *CMakeLists.txt* file.
Once the *tarball ContourTriangulator.tar* has been downloaded and extracted,
```
cd ContourTriangulator/build 
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
./ContourTriangulator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

