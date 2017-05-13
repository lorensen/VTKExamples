[VTKExamples](/home/)/[Cxx](/Cxx)/DataStructures/KdTreePointLocator/ClosestNPoints

**ClosestNPoints.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkIdList.h>
#include <vtkKdTreePointLocator.h>

int main(int, char *[])
{
  //Create some random points
  vtkSmartPointer<vtkPointSource> pointSource =
      vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(10);
  pointSource->Update();

  //Create the tree
  vtkSmartPointer<vtkKdTreePointLocator> pointTree =
      vtkSmartPointer<vtkKdTreePointLocator>::New();
  pointTree->SetDataSet(pointSource->GetOutput());
  pointTree->BuildLocator();

  // Find the k closest points to (0,0,0)
  unsigned int k = 1;
  double testPoint[3] = {0.0, 0.0, 0.0};
  vtkSmartPointer<vtkIdList> result =
      vtkSmartPointer<vtkIdList>::New();

  pointTree->FindClosestNPoints(k, testPoint, result);

  for(vtkIdType i = 0; i < k; i++)
  {
    vtkIdType point_ind = result->GetId(i);
    double p[3];
    pointSource->GetOutput()->GetPoint(point_ind, p);
    std::cout << "Closest point " << i << ": Point "
      << point_ind << ": (" << p[0] << ", " << p[1] << ", " << p[2] << ")" << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ClosestNPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ClosestNPoints MACOSX_BUNDLE ClosestNPoints.cxx)
 
target_link_libraries(ClosestNPoints ${VTK_LIBRARIES})
```

**Download and Build ClosestNPoints**

Click [here to download ClosestNPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ClosestNPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball ClosestNPoints.tar* has been downloaded and extracted,
```
cd ClosestNPoints/build 
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
./ClosestNPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

