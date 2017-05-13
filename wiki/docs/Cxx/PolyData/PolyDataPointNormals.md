[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/PolyDataPointNormals

### Description
This demo adds a normal to each point in a polydata.

**PolyDataPointNormals.cxx**
```c++
#include <vtkCellData.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  ///////// Set Point Normals ///////////
  // Create 3 points
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);

  // Add the points to a polydata
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Set point normals
  vtkSmartPointer<vtkDoubleArray> pointNormalsArray =
    vtkSmartPointer<vtkDoubleArray>::New();
  pointNormalsArray->SetNumberOfComponents(3); //3d normals (ie x,y,z)
  pointNormalsArray->SetNumberOfTuples(polydata->GetNumberOfPoints());

  // Construct the normal vectors
  double pN1[3] = {1.0, 0.0, 0.0};
  double pN2[3] = {0.0, 1.0, 0.0};
  double pN3[3] = {0.0, 0.0, 1.0};

  // Add the data to the normals array
  pointNormalsArray->SetTuple(0, pN1) ;
  pointNormalsArray->SetTuple(1, pN2) ;
  pointNormalsArray->SetTuple(2, pN3) ;

  // Add the normals to the points in the polydata
  polydata->GetPointData()->SetNormals(pointNormalsArray);

  ///////// Get Point Normals ///////////
  vtkSmartPointer<vtkDoubleArray> pointNormalsRetrieved =
    vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetNormals());
  if(pointNormalsRetrieved)
  {
    std::cout << "There are " << pointNormalsRetrieved->GetNumberOfTuples()
              << " point normals." << std::endl;

    for(vtkIdType i = 0; i < pointNormalsRetrieved->GetNumberOfTuples(); i++)
    {
      double pN[3];
      pointNormalsRetrieved->GetTuple(i, pN);
      std::cout << "Point normal " << i << ": "
                << pN[0] << " " << pN[1] << " " << pN[2] << std::endl;
    }

  }//end if(pointNormalsRetrieved)
  else
  {
    std::cout << "No point normals." << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataPointNormals)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataPointNormals MACOSX_BUNDLE PolyDataPointNormals.cxx)
 
target_link_libraries(PolyDataPointNormals ${VTK_LIBRARIES})
```

**Download and Build PolyDataPointNormals**

Click [here to download PolyDataPointNormals](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataPointNormals.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataPointNormals.tar* has been downloaded and extracted,
```
cd PolyDataPointNormals/build 
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
./PolyDataPointNormals
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

