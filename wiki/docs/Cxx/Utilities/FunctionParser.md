[VTKExamples](Home)/[Cxx](Cxx)/Utilities/FunctionParser

### Description
This example shows how to substitute values and evaluate a string such as "a+b".

**FunctionParser.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFunctionParser.h>


int main(int, char *[])
{
  vtkSmartPointer<vtkFunctionParser> functionParser = 
      vtkSmartPointer<vtkFunctionParser>::New();
  functionParser->SetFunction("a+b");
  
  functionParser->SetScalarVariableValue( "a", 2);
  functionParser->SetScalarVariableValue( "b", 3);
    
  double result = functionParser->GetScalarResult();
  
  std::cout << "result: " << result << std::endl;
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FunctionParser)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FunctionParser MACOSX_BUNDLE FunctionParser.cxx)
 
target_link_libraries(FunctionParser ${VTK_LIBRARIES})
```

**Download and Build FunctionParser**

Click [here to download FunctionParser](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FunctionParser.tar) and its *CMakeLists.txt* file.
Once the *tarball FunctionParser.tar* has been downloaded and extracted,
```
cd FunctionParser/build 
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
./FunctionParser
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

