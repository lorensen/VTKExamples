[VTKExamples](Home)/[Cxx](Cxx)/Meshes/MatrixMathFilter

<img align="right" src="https://github.com/lorensen/VTKExamples/raw/master/Testing/Baseline/Meshes/TestMatrixMathFilter.png" width="256" />

**MatrixMathFilter.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkSphereSource.h>
#include <vtkMatrixMathFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkXMLPolyDataWriter.h>

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    std::cerr << "Required arguments: vtkFile" << std::endl;
    return EXIT_FAILURE;
  }

  std::string filename = argv[1]; // "/Data/tensors.vtk";
  
  std::cout << "filename: " << filename << std::endl;

  vtkSmartPointer<vtkUnstructuredGridReader> reader =
    vtkSmartPointer<vtkUnstructuredGridReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter =
    vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  surfaceFilter->SetInputConnection(reader->GetOutputPort());
  surfaceFilter->Update();
  
  vtkSmartPointer<vtkMatrixMathFilter> matrixMathFilter =
    vtkSmartPointer<vtkMatrixMathFilter>::New();
  //matrixMathFilter->SetOperationToDeterminant();
  matrixMathFilter->SetOperationToEigenvalue();
  matrixMathFilter->SetInputConnection(surfaceFilter->GetOutputPort());
  matrixMathFilter->Update();
  matrixMathFilter->GetOutput()->GetPointData()->SetActiveScalars("Eigenvalue");

  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetInputConnection(matrixMathFilter->GetOutputPort());
  writer->SetFileName("output.vtp");
  writer->Write();
  
  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(matrixMathFilter->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
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
 
PROJECT(MatrixMathFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MatrixMathFilter MACOSX_BUNDLE MatrixMathFilter.cxx)
 
target_link_libraries(MatrixMathFilter ${VTK_LIBRARIES})
```

**Download and Build MatrixMathFilter**

Click [here to download MatrixMathFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MatrixMathFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball MatrixMathFilter.tar* has been downloaded and extracted,
```
cd MatrixMathFilter/build 
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
./MatrixMathFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

