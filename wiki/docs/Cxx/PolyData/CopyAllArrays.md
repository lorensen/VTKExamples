[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/CopyAllArrays

**CopyAllArrays.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>

void ManualMethod(vtkPolyData* input);
void AutomaticMethod(vtkPolyData* input);

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  vtkPolyData* polydata = sphereSource->GetOutput();

  vtkSmartPointer<vtkDoubleArray> doubles =
    vtkSmartPointer<vtkDoubleArray>::New();
  doubles->SetName("Doubles");
  doubles->SetNumberOfTuples(polydata->GetNumberOfPoints());

  polydata->GetPointData()->AddArray(doubles);

  vtkSmartPointer<vtkIntArray> ints =
    vtkSmartPointer<vtkIntArray>::New();
  ints->SetName("Ints");
  ints->SetNumberOfTuples(polydata->GetNumberOfPoints());

  polydata->GetPointData()->AddArray(ints);

  ManualMethod(polydata);
  AutomaticMethod(polydata);

  return EXIT_SUCCESS;
}

void ManualMethod(vtkPolyData* input)
{
  unsigned int numberOfArrays = input->GetPointData()->GetNumberOfArrays();
  std::cout << "There are " << numberOfArrays << " arrays." << std::endl;

  vtkSmartPointer<vtkPolyData> newPolyData =
    vtkSmartPointer<vtkPolyData>::New();

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << input->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << input->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;

    newPolyData->GetPointData()->AddArray(input->GetPointData()->GetArray(i));
  }

  std::cout << "new polydata: " << std::endl;

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << newPolyData->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << newPolyData->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;
  }

}

void AutomaticMethod(vtkPolyData* input)
{
  unsigned int numberOfArrays = input->GetPointData()->GetNumberOfArrays();
  std::cout << "There are " << numberOfArrays << " arrays." << std::endl;

  vtkSmartPointer<vtkPolyData> newPolyData =
    vtkSmartPointer<vtkPolyData>::New();

  newPolyData->GetPointData()->PassData(input->GetPointData());

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << input->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << input->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;
  }

  std::cout << "new polydata: " << std::endl;

  for(unsigned int i = 0; i < numberOfArrays; i++)
  {
    std::cout << "array " << i << ":" << std::endl;
    std::cout << "name: " << newPolyData->GetPointData()->GetArrayName(i) << std::endl;
    std::cout << "type: " << newPolyData->GetPointData()->GetArray(i)->GetDataType() << std::endl;
    std::cout << std::endl;
  }

}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CopyAllArrays)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CopyAllArrays MACOSX_BUNDLE CopyAllArrays.cxx)
 
target_link_libraries(CopyAllArrays ${VTK_LIBRARIES})
```

**Download and Build CopyAllArrays**

Click [here to download CopyAllArrays](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CopyAllArrays.tar) and its *CMakeLists.txt* file.
Once the *tarball CopyAllArrays.tar* has been downloaded and extracted,
```
cd CopyAllArrays/build 
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
./CopyAllArrays
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

