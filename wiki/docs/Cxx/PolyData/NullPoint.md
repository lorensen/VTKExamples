[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/NullPoint

**NullPoint.cxx**
```c++
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1,1,1);
  points->InsertNextPoint(2,2,2);
  points->InsertNextPoint(3,3,3);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  vtkSmartPointer<vtkFloatArray> floatArray =
    vtkSmartPointer<vtkFloatArray>::New();
  floatArray->SetNumberOfValues(3);
  floatArray->SetNumberOfComponents(1);
  floatArray->SetName("FloatArray");
  for(vtkIdType i = 0; i < 3; i++)
  {
    floatArray->SetValue(i,2);
  }
  polydata->GetPointData()->AddArray(floatArray);

  vtkSmartPointer<vtkIntArray> intArray =
    vtkSmartPointer<vtkIntArray>::New();
  intArray->SetNumberOfValues(3);
  intArray->SetNumberOfComponents(1);
  intArray->SetName("IntArray");
  for(vtkIdType i = 0; i < 3; i++)
  {
    intArray->SetValue(i,2);
  }

  polydata->GetPointData()->AddArray(intArray);

  for(vtkIdType i = 0; i < 3; i++)
  {
    double p[3];
    polydata->GetPoint(i,p);
    vtkFloatArray* pointsFloatArray = vtkFloatArray::SafeDownCast(polydata->GetPointData()->GetArray("FloatArray"));
    vtkIntArray* pointsIntArray = vtkIntArray::SafeDownCast(polydata->GetPointData()->GetArray("IntArray"));
    std::cout << "Point " << i << " : " << p[0] << " " << p[1] << " " << p[2] << " "
              << pointsFloatArray->GetValue(i) << " " << pointsIntArray->GetValue(i) << std::endl;
  }

  polydata->GetPointData()->NullPoint(1);
  polydata->Modified();

  for(vtkIdType i = 0; i < 3; i++)
  {
    double p[3];
    polydata->GetPoint(i,p);
    vtkFloatArray* pointsFloatArray = vtkFloatArray::SafeDownCast(polydata->GetPointData()->GetArray("FloatArray"));
    vtkIntArray* pointsIntArray = vtkIntArray::SafeDownCast(polydata->GetPointData()->GetArray("IntArray"));
    std::cout << "Point " << i << " : " << p[0] << " " << p[1] << " " << p[2] << " "
              << pointsFloatArray->GetValue(i) << " " << pointsIntArray->GetValue(i) << std::endl;

  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(NullPoint)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(NullPoint MACOSX_BUNDLE NullPoint.cxx)
 
target_link_libraries(NullPoint ${VTK_LIBRARIES})
```

**Download and Build NullPoint**

Click [here to download NullPoint](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/NullPoint.tar) and its *CMakeLists.txt* file.
Once the *tarball NullPoint.tar* has been downloaded and extracted,
```
cd NullPoint/build 
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
./NullPoint
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

