[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/GetMiscPointData

### Description
This example demonstrates how to get data stored at each point in a polydata.

**GetMiscPointData.cxx**
```c++
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkPolyDataNormals.h>
#include <string>

int main(int argc, char *argv[])
{
  // Parse command line arguments
  if(argc != 3)
  {
    std::cout << "Required arguments: Filename ArrayName" << std::endl;
    return EXIT_FAILURE;
  }

  // Get filename from command line
  std::string filename = argv[1]; //first command line argument

  // Get array name
  std::string arrayName = argv[2]; //second command line argument
	
  // Read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  std::cout << "Reading " << filename << std::endl;
  reader->SetFileName(filename.c_str());
  reader->Update();

  // Extract the polydata
  vtkSmartPointer<vtkPolyData> polydata =
    reader->GetOutput();

  // Get the number of points in the polydata
  vtkIdType idNumPointsInFile = polydata->GetNumberOfPoints();

  vtkSmartPointer<vtkDoubleArray> array =
    vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetArray(arrayName.c_str()));

  if(array)
  {
      std::cout << "Got array " << arrayName
                << " with " << idNumPointsInFile << " values"
                << std::endl;
    for(int i = 0; i < idNumPointsInFile; i++)
    {
      double value;
      value = array->GetValue(i);
      std::cout << i << ": " << value << std::endl;
    }
  }
  else
  {
    std::cout << "The file " << filename
              << " does not have a PointData array named " << arrayName
              << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GetMiscPointData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GetMiscPointData MACOSX_BUNDLE GetMiscPointData.cxx)
 
target_link_libraries(GetMiscPointData ${VTK_LIBRARIES})
```

**Download and Build GetMiscPointData**

Click [here to download GetMiscPointData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GetMiscPointData.tar) and its *CMakeLists.txt* file.
Once the *tarball GetMiscPointData.tar* has been downloaded and extracted,
```
cd GetMiscPointData/build 
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
./GetMiscPointData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

