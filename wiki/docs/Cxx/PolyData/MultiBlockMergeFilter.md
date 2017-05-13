[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/MultiBlockMergeFilter

**MultiBlockMergeFilter.cxx**
```c++
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkMultiBlockMergeFilter.h>
#include <vtkMultiBlockDataSet.h>

int main(int, char *[])
{

  vtkSmartPointer<vtkSphereSource> sphereSource1 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->Update();
  
  vtkSmartPointer<vtkSphereSource> sphereSource2 =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource2->SetCenter(10,10,10);
  sphereSource2->Update();

  vtkSmartPointer<vtkMultiBlockDataSet> multiBlockDataSet1 =
    vtkSmartPointer<vtkMultiBlockDataSet>::New();
  multiBlockDataSet1->SetNumberOfBlocks(1);
  multiBlockDataSet1->SetBlock(0, sphereSource1->GetOutput());
#if VTK_MAJOR_VERSION <= 5
  multiBlockDataSet1->Update();
#endif

  vtkSmartPointer<vtkMultiBlockDataSet> multiBlockDataSet2 =
    vtkSmartPointer<vtkMultiBlockDataSet>::New();
  multiBlockDataSet2->SetNumberOfBlocks(1);
  multiBlockDataSet2->SetBlock(0, sphereSource2->GetOutput());
#if VTK_MAJOR_VERSION <= 5
  multiBlockDataSet2->Update();
#endif
  
  vtkSmartPointer<vtkMultiBlockMergeFilter> multiBlockMergeFilter =
      vtkSmartPointer<vtkMultiBlockMergeFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  multiBlockMergeFilter->AddInput(multiBlockDataSet1);
  multiBlockMergeFilter->AddInput(multiBlockDataSet2);
#else
  multiBlockMergeFilter->AddInputData(multiBlockDataSet1);
  multiBlockMergeFilter->AddInputData(multiBlockDataSet2);
#endif
  multiBlockMergeFilter->Update();
  
  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(MultiBlockMergeFilter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(MultiBlockMergeFilter MACOSX_BUNDLE MultiBlockMergeFilter.cxx)
 
target_link_libraries(MultiBlockMergeFilter ${VTK_LIBRARIES})
```

**Download and Build MultiBlockMergeFilter**

Click [here to download MultiBlockMergeFilter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/MultiBlockMergeFilter.tar) and its *CMakeLists.txt* file.
Once the *tarball MultiBlockMergeFilter.tar* has been downloaded and extracted,
```
cd MultiBlockMergeFilter/build 
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
./MultiBlockMergeFilter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

