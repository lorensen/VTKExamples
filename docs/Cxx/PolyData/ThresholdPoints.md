[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/ThresholdPoints

**ThresholdPoints.cxx**
```c++
#include <vtkVersion.h>
#include <vtkIntArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>
#include <vtkThresholdPoints.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0,0,0);
  points->InsertNextPoint(1,1,1);
  points->InsertNextPoint(2,2,2);
  points->InsertNextPoint(3,3,3);
  points->InsertNextPoint(4,4,4);

  std::cout << "There are " << points->GetNumberOfPoints()
            << " points before thresholding." << std::endl;

  //setup position index
  vtkSmartPointer<vtkIntArray> index =
    vtkSmartPointer<vtkIntArray>::New();
  index->SetNumberOfComponents(1);
  index->SetName("index");
  index->InsertNextValue(0);
  index->InsertNextValue(1);
  index->InsertNextValue(2);
  index->InsertNextValue(3);
  index->InsertNextValue(4);

  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->GetPointData()->AddArray(index);

  vtkSmartPointer<vtkThresholdPoints> threshold =
    vtkSmartPointer<vtkThresholdPoints>::New();
#if VTK_MAJOR_VERSION <= 5
  threshold->SetInput(polydata);
#else
  threshold->SetInputData(polydata);
#endif
  threshold->ThresholdByLower(2);
  threshold->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "index");
  threshold->Update();

  //vtkPolyData* thresholdedPolydata = threshold->GetOutput();
  vtkPolyData* thresholdedPolydata = threshold->GetOutput();
  std::cout << "There are " << thresholdedPolydata->GetNumberOfPoints()
            << " points after thresholding." << std::endl;
  for(vtkIdType i = 0; i < thresholdedPolydata->GetNumberOfPoints(); i++)
  {
    double p[3];
    thresholdedPolydata->GetPoint(i,p);
    std::cout << "Point " << i << " : " << p[0] << " " << p[1] << " " << p[2] << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ThresholdPoints)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ThresholdPoints MACOSX_BUNDLE ThresholdPoints.cxx)
 
target_link_libraries(ThresholdPoints ${VTK_LIBRARIES})
```

**Download and Build ThresholdPoints**

Click [here to download ThresholdPoints](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ThresholdPoints.tar) and its *CMakeLists.txt* file.
Once the *tarball ThresholdPoints.tar* has been downloaded and extracted,
```
cd ThresholdPoints/build 
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
./ThresholdPoints
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

