[VTKExamples](/index/)/[Cxx](/Cxx)/IO/ReadPLOT3D

<img align="right" src="https://github.com/lorensen/VTKExamples/blob/gh-pages/Testing/Baseline/IO/TestReadPLOT3D.png?raw=true" width="256" />

**ReadPLOT3D.cxx**
```c++
#include <vtkVersion.h>
#include <vtkPolyData.h>
#if VTK_MAJOR_VERSION <= 5
#include <vtkPLOT3DReader.h>
#else
#include <vtkMultiBlockPLOT3DReader.h>
#include <vtkMultiBlockDataSet.h>
#endif
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>

int main ( int argc, char *argv[] )
{
  if(argc < 3)
  {
    std::cout << "Required parameters: XYZFilename.bin QFileName.bin" << std::endl;
    return EXIT_FAILURE;
  }

  std::string xyzFilename = argv[1];
  std::string qFilename = argv[2];

#if VTK_MAJOR_VERSION <= 5
  vtkSmartPointer<vtkPLOT3DReader> reader =
    vtkSmartPointer<vtkPLOT3DReader>::New();
#else
  vtkSmartPointer<vtkMultiBlockPLOT3DReader> reader =
    vtkSmartPointer<vtkMultiBlockPLOT3DReader>::New();
#endif
  reader->SetXYZFileName(xyzFilename.c_str());
  reader->SetQFileName(qFilename.c_str());
  reader->SetScalarFunctionNumber(100);
  reader->SetVectorFunctionNumber(202);
  reader->Update();

  vtkSmartPointer<vtkStructuredGridGeometryFilter> geometryFilter =
    vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  geometryFilter->SetInputConnection(reader->GetOutputPort());
#else
  geometryFilter->SetInputData(reader->GetOutput()->GetBlock(0));
#endif
  geometryFilter->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(geometryFilter->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReadPLOT3D)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReadPLOT3D MACOSX_BUNDLE ReadPLOT3D.cxx)
 
target_link_libraries(ReadPLOT3D ${VTK_LIBRARIES})
```

**Download and Build ReadPLOT3D**

Click [here to download ReadPLOT3D](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReadPLOT3D.tar) and its *CMakeLists.txt* file.
Once the *tarball ReadPLOT3D.tar* has been downloaded and extracted,
```
cd ReadPLOT3D/build 
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
./ReadPLOT3D
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

