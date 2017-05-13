[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/ArrayCalculator

**ArrayCalculator.cxx**
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
  array->SetName("orig");
  array->InsertNextValue(1.0);
  array->InsertNextValue(2.0);
  array->InsertNextValue(3.0);

  vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->AddArray(array);

  vtkSmartPointer<vtkArrayCalculator> calc1 =
      vtkSmartPointer<vtkArrayCalculator>::New();
#if VTK_MAJOR_VERSION <= 5
  calc1->SetInput(polydata);
#else
  calc1->SetInputData(polydata);
#endif
  calc1->AddScalarArrayName("orig");
  calc1->SetFunction("orig+1");
  calc1->SetResultArrayName("orig");
  calc1->Update();

  vtkSmartPointer<vtkDoubleArray> output1 =
    vtkDoubleArray::SafeDownCast(
      calc1->GetPolyDataOutput()->GetPointData()->GetArray("orig"));

  for(vtkIdType i = 0; i < output1->GetNumberOfTuples(); i++)
  {
    double val = output1->GetValue(i);
    cout << "output1 value " << i << ": " << val << endl;
  }

  vtkSmartPointer<vtkArrayCalculator> calc2 =
      vtkSmartPointer<vtkArrayCalculator>::New();
#if VTK_MAJOR_VERSION <= 5
  calc2->SetInput(polydata);
#else
  calc2->SetInputData(polydata);
#endif
  calc2->AddScalarArrayName("orig");
  calc2->SetFunction("if(orig=2,1,orig)");
  calc2->SetResultArrayName("new");
  calc2->Update();

  vtkSmartPointer<vtkDoubleArray> output2 =
    vtkDoubleArray::SafeDownCast(
      calc2->GetPolyDataOutput()->GetPointData()->GetArray("new"));

  for(vtkIdType i = 0; i < output2->GetNumberOfTuples(); i++)
  {
    double val = output2->GetValue(i);
    cout << "output2 value " << i << ": " << val << endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ArrayCalculator)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ArrayCalculator MACOSX_BUNDLE ArrayCalculator.cxx)
 
target_link_libraries(ArrayCalculator ${VTK_LIBRARIES})
```

**Download and Build ArrayCalculator**

Click [here to download ArrayCalculator](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ArrayCalculator.tar) and its *CMakeLists.txt* file.
Once the *tarball ArrayCalculator.tar* has been downloaded and extracted,
```
cd ArrayCalculator/build 
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
./ArrayCalculator
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

