[VTKExamples](/index/)/[Cxx](/Cxx)/DataStructures/BuildOctree

**BuildOctree.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkIdList.h>
#include <vtkOctreePointLocator.h>
#include <vtkDataSetCollection.h>

int main(int, char *[])
{
  // Setup point coordinates
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 1.0, 0.0};
  double z[3] = {0.0, 0.0, 1.0};

  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> vertices =
    vtkSmartPointer<vtkCellArray>::New();

  for(unsigned int i = 0; i < 3; ++i)
  {
    points->InsertNextPoint ( x[i], y[i], z[i] );
  }

  std::cout << "There are " << points->GetNumberOfPoints() << " points." << std::endl;

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  //Create the tree
  vtkSmartPointer<vtkOctreePointLocator> octree =
      vtkSmartPointer<vtkOctreePointLocator>::New();
  octree->SetDataSet(polydata);
  octree->BuildLocator();

  std::cout << "Number of points in tree: " << octree->GetDataSet()->GetNumberOfPoints() << std::endl;

  double p[3];
  octree->GetDataSet()->GetPoint(0,p);
  std::cout << "p: " << p[0] << " " << p[1] << " " << p[2] << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(BuildOctree)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(BuildOctree MACOSX_BUNDLE BuildOctree.cxx)
 
target_link_libraries(BuildOctree ${VTK_LIBRARIES})
```

**Download and Build BuildOctree**

Click [here to download BuildOctree](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/BuildOctree.tar) and its *CMakeLists.txt* file.
Once the *tarball BuildOctree.tar* has been downloaded and extracted,
```
cd BuildOctree/build 
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
./BuildOctree
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

