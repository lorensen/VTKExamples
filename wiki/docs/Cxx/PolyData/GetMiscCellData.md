[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/GetMiscCellData

**GetMiscCellData.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCellData.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkTriangle.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>

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
	
  //read the file
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();
	
  vtkPolyData* polydata = reader->GetOutput();
	
  // Get the number of cells in the polydata
  vtkIdType idNumCellsInFile = polydata->GetNumberOfCells();

  vtkSmartPointer<vtkFloatArray> array =
    vtkFloatArray::SafeDownCast(polydata->GetCellData()->GetArray(arrayName.c_str()));

  if(array)
  {
    std::cout << "Got array " << arrayName
              << " with " << idNumCellsInFile << " values"
              << std::endl;
    for(int i = 0; i < idNumCellsInFile; i++)
    {
      double value;
      value = array->GetValue(i);
      std::cout << i << ": " << value << std::endl;
    }
  }
  else
  {
    std::cout << "The file " << filename
              << " does not have a CellData array named " << arrayName
              << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(GetMiscCellData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(GetMiscCellData MACOSX_BUNDLE GetMiscCellData.cxx)
 
target_link_libraries(GetMiscCellData ${VTK_LIBRARIES})
```

**Download and Build GetMiscCellData**

Click [here to download GetMiscCellData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/GetMiscCellData.tar) and its *CMakeLists.txt* file.
Once the *tarball GetMiscCellData.tar* has been downloaded and extracted,
```
cd GetMiscCellData/build 
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
./GetMiscCellData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

