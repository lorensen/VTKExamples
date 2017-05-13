[VTKExamples](/home/)/[Cxx](/Cxx)/Math/VectorDot

### Description
Note that the filter maps the values to a scalar range. In the example, the values of the dot products are 
 1, .707, 0

The filter outputs
 1, .414, -1

because the default scalar range that the filter maps the values to is [](-1,1).

**VectorDot.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkVectorDot.h>

// For compatibility with new VTK generic data arrays
#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main(int, char *[])
{
  // Generate data
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);
  points->InsertNextPoint(2,0,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Add normals
  vtkSmartPointer<vtkFloatArray> normals =
    vtkSmartPointer<vtkFloatArray>::New();
  normals->SetNumberOfComponents(3);
  normals->SetName("Normals");

  float n0[3] = {1,0,0};
  float n1[3] = {1,0,0};
  float n2[3] = {1,0,0};
  normals->InsertNextTupleValue(n0);
  normals->InsertNextTupleValue(n1);
  normals->InsertNextTupleValue(n2);

  polydata->GetPointData()->SetNormals(normals);

  // Add vectors
  vtkSmartPointer<vtkFloatArray> vectors =
    vtkSmartPointer<vtkFloatArray>::New();
  vectors->SetNumberOfComponents(3);
  vectors->SetName("Vectors");

  float v0[3] = {1,0,0};
  float v1[3] = {.707f,.707f,0};
  float v2[3] = {0,1,0};
  vectors->InsertNextTupleValue(v0);
  vectors->InsertNextTupleValue(v1);
  vectors->InsertNextTupleValue(v2);

  polydata->GetPointData()->SetVectors(vectors);

  // Compute the dot products between normals and vectors
  vtkSmartPointer<vtkVectorDot> vectorDot =
      vtkSmartPointer<vtkVectorDot>::New();
#if VTK_MAJOR_VERSION <= 5
  vectorDot->SetInputConnection(polydata->GetProducerPort());
#else
  vectorDot->SetInputData(polydata);
#endif
  vectorDot->Update();

  // Get the results
  vtkFloatArray* scalars = vtkFloatArray::SafeDownCast ( vectorDot->GetOutput()->GetPointData()->GetScalars() );

  // Output the results
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
 
PROJECT(VectorDot)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(VectorDot MACOSX_BUNDLE VectorDot.cxx)
 
target_link_libraries(VectorDot ${VTK_LIBRARIES})
```

**Download and Build VectorDot**

Click [here to download VectorDot](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/VectorDot.tar) and its *CMakeLists.txt* file.
Once the *tarball VectorDot.tar* has been downloaded and extracted,
```
cd VectorDot/build 
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
./VectorDot
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

