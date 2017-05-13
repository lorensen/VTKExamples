[VTKExamples](/home/)/[Cxx](/Cxx)/Math/VectorNorm

**VectorNorm.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkVectorNorm.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1,2,3);
  points->InsertNextPoint(4,5,6);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetNumberOfComponents(3);
  distances->SetName("Distances");

  float v1[3] = {1,2,3};
  float v2[3] = {4,5,6};
  distances->InsertNextTupleValue(v1);
  distances->InsertNextTupleValue(v2);

  polydata->GetPointData()->SetVectors(distances);

  vtkSmartPointer<vtkVectorNorm> vectorNorm =
    vtkSmartPointer<vtkVectorNorm>::New();
#if VTK_MAJOR_VERSION <= 5
  vectorNorm->SetInputConnection(polydata->GetProducerPort());
#else
  vectorNorm->SetInputData(polydata);
#endif
  vectorNorm->Update();

  vtkFloatArray* scalars = vtkFloatArray::SafeDownCast ( vectorNorm->GetOutput()->GetPointData()->GetScalars() );

  for(vtkIdType i = 0; i < scalars->GetNumberOfTuples(); i++)
  {
    std::cout << "Value " << i << " : " << scalars->GetValue(i) << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(VectorNorm)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorNorm MACOSX_BUNDLE VectorNorm.cxx)
 
target_link_libraries(VectorNorm ${VTK_LIBRARIES})
```

**Download and Build VectorNorm**

Click [here to download VectorNorm](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorNorm.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorNorm.tar* has been downloaded and extracted,
```
cd VectorNorm/build 
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
./VectorNorm
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

