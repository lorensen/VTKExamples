[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/DeletePoint

**DeletePoint.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

void OutputPoints(vtkSmartPointer<vtkPoints> points);
void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkIdType id);

int main(int, char *[])
{
  // Create a set of points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint ( 1.0, 0.0, 0.0 );
  points->InsertNextPoint ( 0.0, 1.0, 0.0 );
  points->InsertNextPoint ( 0.0, 0.0, 1.0 );

  std::cout << "Number of points: " << points->GetNumberOfPoints() << std::endl;
  OutputPoints(points);

  ReallyDeletePoint(points, 1);

  std::cout << "Number of points: " << points->GetNumberOfPoints() << std::endl;
  OutputPoints(points);

  return EXIT_SUCCESS;
}

void OutputPoints(vtkSmartPointer<vtkPoints> points)
{
  for(vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
  {
    double p[3];
    points->GetPoint(i,p);
    cout << p[0] << " " << p[1] << " " << p[2] << endl;
  }
}

void ReallyDeletePoint(vtkSmartPointer<vtkPoints> points, vtkIdType id)
{
  vtkSmartPointer<vtkPoints> newPoints =
    vtkSmartPointer<vtkPoints>::New();

  for(vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
  {
    if(i != id)
    {
      double p[3];
      points->GetPoint(i,p);
      newPoints->InsertNextPoint(p);
    }
  }

  points->ShallowCopy(newPoints);
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DeletePoint)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DeletePoint MACOSX_BUNDLE DeletePoint.cxx)
 
target_link_libraries(DeletePoint ${VTK_LIBRARIES})
```

**Download and Build DeletePoint**

Click [here to download DeletePoint](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DeletePoint.tar) and its *CMakeLists.txt* file.
Once the *tarball DeletePoint.tar* has been downloaded and extracted,
```
cd DeletePoint/build 
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
./DeletePoint
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

