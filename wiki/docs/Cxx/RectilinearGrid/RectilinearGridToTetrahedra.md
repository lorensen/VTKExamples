[VTKExamples](/home/)/[Cxx](/Cxx)/RectilinearGrid/RectilinearGridToTetrahedra


**RectilinearGridToTetrahedra.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkRectilinearGrid.h>
#include <vtkRectilinearGridToTetrahedra.h>
#include <vtkUnstructuredGrid.h>
#include <vtkMath.h>
#include <vtkDoubleArray.h>
 
int main(int, char *[])
{
  // Create a grid
  vtkSmartPointer<vtkRectilinearGrid> grid = 
    vtkSmartPointer<vtkRectilinearGrid>::New();
 
  grid->SetDimensions(5,4,3);
 
  vtkSmartPointer<vtkDoubleArray> xArray = 
    vtkSmartPointer<vtkDoubleArray>::New();
  xArray->InsertNextValue(0.0);
  xArray->InsertNextValue(1.0);
  xArray->InsertNextValue(2.0);
  xArray->InsertNextValue(3.0);
  xArray->InsertNextValue(4.0);

  vtkSmartPointer<vtkDoubleArray> yArray = 
    vtkSmartPointer<vtkDoubleArray>::New();
  yArray->InsertNextValue(0.0);
  yArray->InsertNextValue(1.0);
  yArray->InsertNextValue(2.0);
  yArray->InsertNextValue(3.0);
 
  vtkSmartPointer<vtkDoubleArray> zArray = 
    vtkSmartPointer<vtkDoubleArray>::New();
  zArray->InsertNextValue(0.0);
  zArray->InsertNextValue(1.0);
  zArray->InsertNextValue(2.0);
 
  grid->SetXCoordinates(xArray);
  grid->SetYCoordinates(yArray);
  grid->SetZCoordinates(zArray);
 
  vtkSmartPointer<vtkRectilinearGridToTetrahedra> rectilinearGridToTetrahedra =
    vtkSmartPointer<vtkRectilinearGridToTetrahedra>::New();
#if VTK_MAJOR_VERSION <= 5
  rectilinearGridToTetrahedra->SetInputConnection(grid->GetProducerPort());
#else
  rectilinearGridToTetrahedra->SetInputData(grid);
#endif
  rectilinearGridToTetrahedra->Update();
 
  vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer = 
    vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
  writer->SetFileName("output.vtu");
  writer->SetInputConnection(rectilinearGridToTetrahedra->GetOutputPort());
  writer->Write();
 
  std::cout << "There are " 
            << rectilinearGridToTetrahedra->GetOutput()->GetNumberOfCells()
            << " cells." << std::endl;
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RectilinearGridToTetrahedra)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RectilinearGridToTetrahedra MACOSX_BUNDLE RectilinearGridToTetrahedra.cxx)
 
target_link_libraries(RectilinearGridToTetrahedra ${VTK_LIBRARIES})
```

**Download and Build RectilinearGridToTetrahedra**

Click [here to download RectilinearGridToTetrahedra](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RectilinearGridToTetrahedra.tar) and its *CMakeLists.txt* file.
Once the *tarball RectilinearGridToTetrahedra.tar* has been downloaded and extracted,
```
cd RectilinearGridToTetrahedra/build 
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
./RectilinearGridToTetrahedra
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

