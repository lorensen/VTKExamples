[VTKExamples](Home)/[Cxx](Cxx)/Utilities/ExtractArrayComponent

**ExtractArrayComponent.cxx**
```c++
#include <vtkVersion.h>
#include <vtkArrayCalculator.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(2.0, 0.0, 0.0);
  points->InsertNextPoint(3.0, 0.0, 0.0);

  vtkSmartPointer<vtkDoubleArray> array =
      vtkSmartPointer<vtkDoubleArray>::New();
  array->SetName("InputArray");
  array->SetNumberOfComponents(3);
  array->InsertNextTuple3(1, 10, 100);
  array->InsertNextTuple3(2, 20, 200);
  array->InsertNextTuple3(3, 30, 300);

  vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->AddArray(array);

  vtkSmartPointer<vtkArrayCalculator> arrayCalculator =
      vtkSmartPointer<vtkArrayCalculator>::New();
#if VTK_MAJOR_VERSION <= 5
  arrayCalculator->SetInput(polydata);
#else
  arrayCalculator->SetInputData(polydata);
#endif
  arrayCalculator->AddVectorArrayName("InputArray");
  arrayCalculator->SetFunction("InputArray . jHat"); // Extract component '1' from the InputArray by taking the dot product of each tuple with the vector (0,1,0)
  arrayCalculator->SetResultArrayName("OutputArray");
  arrayCalculator->Update();

  vtkSmartPointer<vtkDoubleArray> outputArray =
    vtkDoubleArray::SafeDownCast(
      arrayCalculator->GetPolyDataOutput()->GetPointData()->GetArray("OutputArray"));

  for(vtkIdType i = 0; i < outputArray->GetNumberOfTuples(); i++)
  {
    double val = outputArray->GetValue(i);
    std::cout << "output value " << i << ": " << val << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ExtractArrayComponent)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ExtractArrayComponent MACOSX_BUNDLE ExtractArrayComponent.cxx)
 
target_link_libraries(ExtractArrayComponent ${VTK_LIBRARIES})
```

**Download and Build ExtractArrayComponent**

Click [here to download ExtractArrayComponent](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ExtractArrayComponent.tar) and its *CMakeLists.txt* file.
Once the *tarball ExtractArrayComponent.tar* has been downloaded and extracted,
```
cd ExtractArrayComponent/build 
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
./ExtractArrayComponent
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

