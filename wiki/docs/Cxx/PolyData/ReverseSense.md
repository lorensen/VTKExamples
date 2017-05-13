[VTKExamples](Home)/[Cxx](Cxx)/PolyData/ReverseSense

**ReverseSense.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkPointData.h>
#include <vtkReverseSense.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkSmartPointer<vtkFloatArray> pointNormals =
    vtkFloatArray::SafeDownCast(sphereSource->GetOutput()->GetPointData()->GetNormals());

  std::cout << std::endl << "Normals: " << std::endl;
  // Display the first few normals
  for(unsigned int i = 0; i < 5; i++)
  {
    double pN[3];
    pointNormals->GetTuple(i, pN);
    std::cout << "Point normal " << i << ": " << pN[0] << " " << pN[1] << " " << pN[2] << std::endl;
  }

  vtkSmartPointer<vtkReverseSense> reverseSense =
    vtkSmartPointer<vtkReverseSense>::New();
  reverseSense->SetInputConnection(sphereSource->GetOutputPort());
  reverseSense->ReverseNormalsOn();
  reverseSense->Update();


  vtkSmartPointer<vtkFloatArray> reversedNormals =
    vtkFloatArray::SafeDownCast(reverseSense->GetOutput()->GetPointData()->GetNormals());

  std::cout << std::endl << "Reversed: " << std::endl;
  // Display the first few normals to verify that they are flipped
  for(unsigned int i = 0; i < 5; i++)
  {
    double pN[3];
    reversedNormals->GetTuple(i, pN);
    std::cout << "Reversed normal " << i << ": " << pN[0] << " " << pN[1] << " " << pN[2] << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ReverseSense)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ReverseSense MACOSX_BUNDLE ReverseSense.cxx)
 
target_link_libraries(ReverseSense ${VTK_LIBRARIES})
```

**Download and Build ReverseSense**

Click [here to download ReverseSense](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ReverseSense.tar) and its *CMakeLists.txt* file.
Once the *tarball ReverseSense.tar* has been downloaded and extracted,
```
cd ReverseSense/build 
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
./ReverseSense
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

