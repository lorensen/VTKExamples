[VTKExamples](/index/)/[Cxx](/Cxx)/DataStructures/KDTreeFindPointsWithinRadius

**KDTreeFindPointsWithinRadius.cxx**
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
  vtkIdType k = 1;
  double testPoint[3] = {0.0, 0.0, 0.0};
  vtkSmartPointer<vtkIdList> result =
      vtkSmartPointer<vtkIdList>::New();

  pointTree->FindPointsWithinRadius(1.0, testPoint, result);

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
 
PROJECT(KDTreeFindPointsWithinRadius)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(KDTreeFindPointsWithinRadius MACOSX_BUNDLE KDTreeFindPointsWithinRadius.cxx)
 
target_link_libraries(KDTreeFindPointsWithinRadius ${VTK_LIBRARIES})
```

**Download and Build KDTreeFindPointsWithinRadius**

Click [here to download KDTreeFindPointsWithinRadius](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/KDTreeFindPointsWithinRadius.tar) and its *CMakeLists.txt* file.
Once the *tarball KDTreeFindPointsWithinRadius.tar* has been downloaded and extracted,
```
cd KDTreeFindPointsWithinRadius/build 
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
./KDTreeFindPointsWithinRadius
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

