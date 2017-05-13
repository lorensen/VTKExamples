[VTKExamples](Home)/[Cxx](Cxx)/DataStructures/KDTreeAccessPoints

### Description
This example demonstrates how to build a KDTree, get its number of points, and get a point by ID.

**KDTreeAccessPoints.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkIdList.h>
#include <vtkKdTree.h>
#include <vtkDataSetCollection.h>
#include <vtkVertexGlyphFilter.h>
 
int main(int, char *[])
{
  //Setup point coordinates
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 1.0, 0.0};
  double z[3] = {0.0, 0.0, 1.0};
 
  vtkSmartPointer<vtkPoints> points = 
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint (x);
  points->InsertNextPoint (y);
  points->InsertNextPoint (z);
  
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  
  //the tree needs cells, so add vertices to each point
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter = 
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexFilter->SetInputConnection(polydata->GetProducerPort());
#else
  vertexFilter->SetInputData(polydata);
#endif
  vertexFilter->Update();
  
  //Create the tree
  vtkSmartPointer<vtkKdTree> kDTree = 
    vtkSmartPointer<vtkKdTree>::New();
  kDTree->AddDataSet(vertexFilter->GetOutput());
  kDTree->BuildLocator();
 
  //get the number of points in the tree like this
  kDTree->GetDataSets()->InitTraversal();
  std::cout << "Number of points in tree: " << kDTree->GetDataSets()->GetNextDataSet()->GetNumberOfPoints() << std::endl;
 
  //or you can get the number of points in the tree like this
  std::cout << "Number of points in tree: " << kDTree->GetDataSet(0)->GetNumberOfPoints() << std::endl;
 
  //get the 0th point in the tree
  double p[3];
  kDTree->GetDataSet(0)->GetPoint(0,p);
  std::cout << "p: " << p[0] << " " << p[1] << " " << p[2] << std::endl;
 
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(KDTreeAccessPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(KDTreeAccessPoints MACOSX_BUNDLE KDTreeAccessPoints.cxx)
 
target_link_libraries(KDTreeAccessPoints ${VTK_LIBRARIES})
```

**Download and Build KDTreeAccessPoints**

Click [here to download KDTreeAccessPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/KDTreeAccessPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball KDTreeAccessPoints.tar* has been downloaded and extracted,
```
cd KDTreeAccessPoints/build 
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
./KDTreeAccessPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

