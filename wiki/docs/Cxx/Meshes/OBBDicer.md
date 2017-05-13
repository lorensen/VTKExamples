[VTKExamples](/index/)/[Cxx](/Cxx)/Meshes/OBBDicer

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/Meshes/TestOBBDicer.png?raw=true" width="256" />

### Description
The vtkOBBDicer filter breaks up an input mesh into a number of pieces. The resulting mesh contains scalar point data that can be used to extract the individual pieces with a filter like vtkThresholdFilter. This examples displays the output of vtkOBBDicer with a different color for each piece.

**OBBDicer.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>

#include <vtkActor.h>
#include <vtkOBBDicer.h>
#include <vtkOutlineCornerFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkXMLPolyDataReader.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkPolyData> inputPolyData;
  if(argc > 1)
  {
    vtkSmartPointer<vtkXMLPolyDataReader> reader =
      vtkSmartPointer<vtkXMLPolyDataReader>::New();
    reader->SetFileName(argv[1]);
    reader->Update();
    inputPolyData = reader->GetOutput();
  }
  else
  {
    vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();
    inputPolyData = sphereSource->GetOutput();
  }

  // Create pipeline
  vtkSmartPointer<vtkOBBDicer> dicer =
    vtkSmartPointer<vtkOBBDicer>::New();
#if VTK_MAJOR_VERSION <= 5
  dicer->SetInput(inputPolyData);
#else
  dicer->SetInputData(inputPolyData);
#endif
  dicer->SetNumberOfPieces(4);
  dicer->SetDiceModeToSpecifiedNumberOfPieces();
  dicer->Update();

  vtkSmartPointer<vtkPolyDataMapper> inputMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  inputMapper->SetInputConnection(dicer->GetOutputPort());
  inputMapper->SetScalarRange(0, dicer->GetNumberOfActualPieces());

  std::cout << "Asked for: "
            << dicer->GetNumberOfPieces() << " pieces, got: "
            << dicer->GetNumberOfActualPieces() << std::endl;

  vtkSmartPointer<vtkActor> inputActor =
    vtkSmartPointer<vtkActor>::New();
  inputActor->SetMapper(inputMapper);
   inputActor->GetProperty()->SetInterpolationToFlat();

  vtkSmartPointer<vtkOutlineCornerFilter> outline =
    vtkSmartPointer<vtkOutlineCornerFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  outline->SetInput(inputPolyData);
#else
  outline->SetInputData(inputPolyData);
#endif

  vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  outlineMapper->SetInputConnection(outline->GetOutputPort());

  vtkSmartPointer<vtkActor> outlineActor =
    vtkSmartPointer<vtkActor>::New();
  outlineActor->SetMapper(outlineMapper);
  outlineActor->GetProperty()->SetColor(0, 0, 0);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size
  renderer->AddActor(outlineActor);
  renderer->AddActor(inputActor);
  renderer->SetBackground(.2, .3, .4);

  // Render the image
  renderWindow->Render();

  interactor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(OBBDicer)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(OBBDicer MACOSX_BUNDLE OBBDicer.cxx)
 
target_link_libraries(OBBDicer ${VTK_LIBRARIES})
```

**Download and Build OBBDicer**

Click [here to download OBBDicer](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/OBBDicer.tar) and its *CMakeLists.txt* file.
Once the *tarball OBBDicer.tar* has been downloaded and extracted,
```
cd OBBDicer/build 
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
./OBBDicer
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

