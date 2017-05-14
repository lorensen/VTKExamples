[VTKExamples](/index/)/[Cxx](/Cxx)/VTKConcepts/Scalars

**Scalars.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>

void TypeSpecific();
void NonTypeSpecific();

int main(int, char *[])
{
  TypeSpecific();
  NonTypeSpecific();
  
  return EXIT_SUCCESS;
}

void TypeSpecific()
{
  // Create a point set
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  vtkSmartPointer<vtkDoubleArray> weights =
    vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfValues(2);
  weights->SetValue(0, 1);
  weights->SetValue(1, 2);
  
  polydata->GetPointData()->SetScalars(weights);
  
  double weight = vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);
  std::cout << "double weight: " << weight << std::endl;
  
  /*
  // This causes a crash because the array is not a vtkFloatArray
  double weightf = vtkFloatArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);
  std::cout << "float weight: " << weightf << std::endl;
  */
}

void NonTypeSpecific()
{
  // Create a point set
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,0,0);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  vtkSmartPointer<vtkDoubleArray> weights =
    vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfValues(2);
  weights->SetValue(0, 1);
  weights->SetValue(1, 2);
  
  polydata->GetPointData()->SetScalars(weights);
  
  double weight = polydata->GetPointData()->GetScalars()->GetComponent(0,0);
  std::cout << "double weight: " << weight << std::endl;
  
  double weightf = polydata->GetPointData()->GetScalars()->GetComponent(0,0);
  std::cout << "float weight: " << weightf << std::endl;

}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(Scalars)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Scalars MACOSX_BUNDLE Scalars.cxx)
 
target_link_libraries(Scalars ${VTK_LIBRARIES})
```

**Download and Build Scalars**

Click [here to download Scalars](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/Scalars.tar) and its *CMakeLists.txt* file.
Once the *tarball Scalars.tar* has been downloaded and extracted,
```
cd Scalars/build 
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
./Scalars
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

