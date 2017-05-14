[VTKExamples](/index/)/[Cxx](/Cxx)/PolyData/FieldData

### Description
Three types of data can be stored in a vtkPolyData object - PointData, CellData, and FieldData. For PointData, there must be a piece of data associated with each point (e.g. a temperature data array with the temperature at each point). For CellData, there must be a piece of data associated with each cell (e.g. the area of each triangle). For data that does not align with either points or cells, FieldData should be used. This is typically data that describes the dataset as a whole. An example could be the name of the dataset, or the center of mass of the points, etc.

This demo adds general data to a polydata (not at each point or cell). In this example, the center of mass of the data is stored.

**FieldData.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkCellData.h>
#include <vtkMath.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkFieldData.h>
#include <vtkSphereSource.h>
 
int main(int, char *[])
{
  vtkSmartPointer<vtkSphereSource> source = 
    vtkSmartPointer<vtkSphereSource>::New();
  source->Update();
 
  // Extract the polydata
  vtkSmartPointer<vtkPolyData> polydata = 
    vtkSmartPointer<vtkPolyData>::New();
  polydata->ShallowCopy(source->GetOutput());
 
  vtkSmartPointer<vtkDoubleArray> location = 
    vtkSmartPointer<vtkDoubleArray>::New();
 
  // Create the data to store (here we just use (0,0,0))
  double locationValue[3] = {0,0,0};
 
  location->SetNumberOfComponents(3);
  location->SetName("MyDoubleArray");
  location->InsertNextTuple(locationValue);
  // The data is added to FIELD data (rather than POINT data as usual)
  polydata->GetFieldData()->AddArray(location);
 
  vtkSmartPointer<vtkIntArray> intValue =
    vtkSmartPointer<vtkIntArray>::New();
  intValue->SetNumberOfComponents(1);
  intValue->SetName("MyIntValue");
  intValue->InsertNextValue(5);

  polydata->GetFieldData()->AddArray(intValue);
 
  // Get the data back out
  vtkIntArray* retrievedArray = vtkIntArray::SafeDownCast(polydata->GetFieldData()->GetAbstractArray("MyIntValue"));

  std::cout << retrievedArray->GetValue(0) << std::endl;

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(FieldData)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FieldData MACOSX_BUNDLE FieldData.cxx)
 
target_link_libraries(FieldData ${VTK_LIBRARIES})
```

**Download and Build FieldData**

Click [here to download FieldData](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/FieldData.tar) and its *CMakeLists.txt* file.
Once the *tarball FieldData.tar* has been downloaded and extracted,
```
cd FieldData/build 
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
./FieldData
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

