[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/RemoveVertices

**RemoveVertices.cxx**
```c++
#include <vtkVersion.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkSmartPointer.h>
#include <vtkCellData.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>

int main ( int argc, char *argv[] )
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " filename.vtp" << std::endl;
    return EXIT_FAILURE;
  }
  std::string filename = argv[1];

  // Read all the data from the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  vtkSmartPointer<vtkPolyData> output = vtkSmartPointer<vtkPolyData>::New();
  output->ShallowCopy(reader->GetOutput());
  //output->SetVerts(NULL);
  vtkSmartPointer<vtkCellArray> verts = vtkSmartPointer<vtkCellArray>::New();
  output->SetVerts(verts);
  //output->SetPoints(reader->GetOutput()->GetPoints());
  //output->SetPolys(reader->GetOutput()->GetPolys());

  vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  writer->SetFileName("test.vtp");
#if VTK_MAJOR_VERSION <= 5
  writer->SetInput(output);
#else
  writer->SetInputData(output);
#endif
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(RemoveVertices)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(RemoveVertices MACOSX_BUNDLE RemoveVertices.cxx)
 
target_link_libraries(RemoveVertices ${VTK_LIBRARIES})
```

**Download and Build RemoveVertices**

Click [here to download RemoveVertices](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/RemoveVertices.tar) and its *CMakeLists.txt* file.
Once the *tarball RemoveVertices.tar* has been downloaded and extracted,
```
cd RemoveVertices/build 
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
./RemoveVertices
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

