[VTKExamples](Home)/[Cxx](Cxx)/PolyData/PointLocatorRadius

**PointLocatorRadius.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkIdList.h>
#include <vtkPolyDataMapper.h>
#include <vtkObjectFactory.h>
#include <vtkPointSource.h>
#include <vtkPolyData.h>
#include <vtkPointLocator.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPointSource> pointSource =
    vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetNumberOfPoints(400);
  pointSource->Update();

  // Create the tree
  vtkSmartPointer<vtkPointLocator> pointLocator =
    vtkSmartPointer<vtkPointLocator>::New();
  pointLocator->SetDataSet(pointSource->GetOutput());
  pointLocator->AutomaticOn();
  pointLocator->SetNumberOfPointsPerBucket(2);
  pointLocator->BuildLocator();

  double radius = .1;
  double center[3] = {0.0, 0.0, 0.0};
  vtkSmartPointer<vtkIdList> result =
    vtkSmartPointer<vtkIdList>::New();
  pointLocator->FindPointsWithinRadius (radius, center, result);

  for(vtkIdType i = 0; i < result->GetNumberOfIds(); i++)
  {
    unsigned int id = result->GetId(i);
    std::cout << "id of point " << i << " : " << id << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PointLocatorRadius)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PointLocatorRadius MACOSX_BUNDLE PointLocatorRadius.cxx)
 
target_link_libraries(PointLocatorRadius ${VTK_LIBRARIES})
```

**Download and Build PointLocatorRadius**

Click [here to download PointLocatorRadius](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PointLocatorRadius.tar) and its *CMakeLists.txt* file.
Once the *tarball PointLocatorRadius.tar* has been downloaded and extracted,
```
cd PointLocatorRadius/build 
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
./PointLocatorRadius
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

