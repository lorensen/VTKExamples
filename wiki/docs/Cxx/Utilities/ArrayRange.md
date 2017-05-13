[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/ArrayRange

**ArrayRange.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>
#include <vtkIntArray.h>

int main(int, char *[])
{
  /////////// Floats ///////////
  {
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetNumberOfComponents(1);
  distances->SetName("Distances");

  distances->InsertNextValue(5);
  distances->InsertNextValue(15);
  distances->InsertNextValue(25);

  // Get min and max
  double range[2];
  distances->GetRange(range);
  std::cout << "range = " << range[0] << " " << range[1] << std::endl;
  }
  
  /////////////// Ints //////////////
  {
  vtkSmartPointer<vtkIntArray> ints =
    vtkSmartPointer<vtkIntArray>::New();
  ints->SetNumberOfComponents(1);
  ints->SetName("Ints");

  ints->InsertNextValue(5);
  ints->InsertNextValue(15);
  ints->InsertNextValue(25);

  // Get min and max
  int valuesRange[2];
  ints->GetValueRange(valuesRange); // Note this is not GetRange()!
  std::cout << "valuesRange = " << valuesRange[0] << " " << valuesRange[1] << std::endl;
  }
  
  /////////// Range with negative values ///////////
  {
  vtkSmartPointer<vtkIntArray> ints =
    vtkSmartPointer<vtkIntArray>::New();
  ints->SetNumberOfComponents(1);
  ints->SetName("Ints");

  ints->InsertNextValue(-50);
  ints->InsertNextValue(15);
  ints->InsertNextValue(25);

  // Get min and max
  int valuesRange[2];
  ints->GetValueRange(valuesRange); // Note this is not GetRange()!
  std::cout << "valuesRange = " << valuesRange[0] << " " << valuesRange[1] << std::endl;
  }

  /////////// Magnitude range ///////////
  {
  vtkSmartPointer<vtkIntArray> ints =
    vtkSmartPointer<vtkIntArray>::New();
  ints->SetNumberOfComponents(1);
  ints->SetName("Ints");

  ints->InsertNextValue(-50);
  ints->InsertNextValue(15);
  ints->InsertNextValue(25);

  // Get min and max
  int valuesRange[2];
  ints->GetValueRange(valuesRange, -1);
  std::cout << "valuesRange = " << valuesRange[0] << " " << valuesRange[1] << std::endl;
  }
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ArrayRange)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ArrayRange MACOSX_BUNDLE ArrayRange.cxx)
 
target_link_libraries(ArrayRange ${VTK_LIBRARIES})
```

**Download and Build ArrayRange**

Click [here to download ArrayRange](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ArrayRange.tar) and its *CMakeLists.txt* file.
Once the *tarball ArrayRange.tar* has been downloaded and extracted,
```
cd ArrayRange/build 
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
./ArrayRange
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

