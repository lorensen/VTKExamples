[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/DetermineArrayDataTypes

### Description
This example shows how to determine the type of data stored in a named array in a vtp file.

**DetermineArrayDataTypes.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkXMLPolyDataReader.h>
#include <vector>
#include <string>

void FindAllData(const std::string &inputFilename);

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0] << " InputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];
  FindAllData(inputFilename);
	
  return EXIT_SUCCESS;
}

void FindAllData(const std::string &InputFilename)
{
  vtkSmartPointer<vtkXMLPolyDataReader> reader =
    vtkSmartPointer<vtkXMLPolyDataReader>::New();
  reader->SetFileName(InputFilename.c_str());
  reader->Update();
  vtkPolyData* polydata = reader->GetOutput();

  unsigned int numberOfArrays = polydata->GetPointData()->GetNumberOfArrays();
  std::cout << "NumArrays: " << numberOfArrays << std::endl;
	
  std::cout << "key: " << std::endl;;
  //more values can be found in <VTK_DIR>/Common/vtkSetGet.h
  std::cout << VTK_UNSIGNED_CHAR << " unsigned char" << std::endl;
  std::cout << VTK_UNSIGNED_INT << " unsigned int" << std::endl;
  std::cout << VTK_FLOAT << " float" << std::endl;
  std::cout << VTK_DOUBLE << " double" << std::endl;
	
  std::vector<std::string> arrayNames;
  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    //the following two lines are equivalent
    //arrayNames.push_back(polydata->GetPointData()->GetArray(i)->GetName());
    arrayNames.push_back(polydata->GetPointData()->GetArrayName(i));
    int dataTypeID = polydata->GetPointData()->GetArray(i)->GetDataType();
    std::cout << "Array " << i << ": " << arrayNames[i] << " (type: " << dataTypeID << ")" << std::endl;
  }
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DetermineArrayDataTypes)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DetermineArrayDataTypes MACOSX_BUNDLE DetermineArrayDataTypes.cxx)
 
target_link_libraries(DetermineArrayDataTypes ${VTK_LIBRARIES})
```

**Download and Build DetermineArrayDataTypes**

Click [here to download DetermineArrayDataTypes](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DetermineArrayDataTypes.tar) and its *CMakeLists.txt* file.
Once the *tarball DetermineArrayDataTypes.tar* has been downloaded and extracted,
```
cd DetermineArrayDataTypes/build 
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
./DetermineArrayDataTypes
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

