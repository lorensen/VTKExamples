[VTKExamples](Home)/[Cxx](Cxx)/PolyData/PointCellIds

**PointCellIds.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkIdFilter.h>
#include <vtkIdTypeArray.h>
#include <vtkPointData.h>
#include <vtkCellData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> sphereSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->Update();

  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfPoints() << " points." << std::endl;
  std::cout << "There are " << sphereSource->GetOutput()->GetNumberOfCells() << " cells." << std::endl;

  vtkSmartPointer<vtkIdFilter> idFilter =
    vtkSmartPointer<vtkIdFilter>::New();
  idFilter->SetInputConnection(sphereSource->GetOutputPort());
  idFilter->SetIdsArrayName("ids");
  idFilter->Update();

  std::cout << "point arrays: " << std::endl;
  for(vtkIdType i = 0; i < idFilter->GetOutput()->GetPointData()->GetNumberOfArrays(); i++)
  {
    std::cout << idFilter->GetOutput()->GetPointData()->GetArrayName(i) << std::endl;
  }

  std::cout << "cell arrays: " << std::endl;
  for(vtkIdType i = 0; i < idFilter->GetOutput()->GetCellData()->GetNumberOfArrays(); i++)
  {
    std::cout << idFilter->GetOutput()->GetCellData()->GetArrayName(i) << std::endl;
  }

  vtkIdTypeArray* pointIds = vtkIdTypeArray::SafeDownCast(idFilter->GetOutput()->GetPointData()->GetArray("ids"));
  std::cout << "There are " << pointIds->GetNumberOfTuples() << " point ids" << std::endl;

  vtkIdTypeArray* cellIds = vtkIdTypeArray::SafeDownCast(idFilter->GetOutput()->GetCellData()->GetArray("ids"));
  std::cout << "There are " << cellIds->GetNumberOfTuples() << " point ids" << std::endl;

  return EXIT_SUCCESS;

}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PointCellIds)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PointCellIds MACOSX_BUNDLE PointCellIds.cxx)
 
target_link_libraries(PointCellIds ${VTK_LIBRARIES})
```

**Download and Build PointCellIds**

Click [here to download PointCellIds](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PointCellIds.tar) and its *CMakeLists.txt* file.
Once the *tarball PointCellIds.tar* has been downloaded and extracted,
```
cd PointCellIds/build 
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
./PointCellIds
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

