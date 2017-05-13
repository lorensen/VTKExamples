[VTKExamples](/home/)/[Cxx](/Cxx)/PolyData/PolyDataCellNormals

### Description
This example shows how to add normals to vertices. This is identical to adding normals to any type of cells. The only difference from [Normals to/from a Polydata]]([Add/Get) is

<source lang="cpp">
polydata->GetPointData()->SetNormals(PointNormalsArray);
</source>

<source lang="cpp">
vtkSmartPointer<vtkDoubleArray> PointNormalsRetrieved = vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetNormals());
</source>

are changed to 


<source lang="cpp">
polydata->GetCellData()->SetNormals(CellNormalsArray);
</source>

and 

<source lang="cpp">
vtkSmartPointer<vtkDoubleArray> CellNormalsRetrieved = vtkDoubleArray::SafeDownCast(polydata->GetCellData()->GetNormals());
</source>

**PolyDataCellNormals.cxx**
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

  //Setup point coordinates
  double x[3] = {1.0, 0.0, 0.0};
  double y[3] = {0.0, 0.0, 1.0};
  double z[3] = {0.0, 0.0, 0.0};

  //create 3 points and add a vertex at each point
  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
  vtkSmartPointer<vtkCellArray> vertices =
      vtkSmartPointer<vtkCellArray>::New();

  for ( unsigned int i = 0; i < 3; ++i )
  {
    //Declare a variable to store the index of the point that gets added. This behaves just like an unsigned int.
    vtkIdType pid[1];

    //Add a point to the polydata and save its index, which we will use to create the vertex on that point.
    pid[0] = points->InsertNextPoint ( x[i], y[i], z[i] );

    //create a vertex cell on the point that was just added.
    vertices->InsertNextCell ( 1,pid );
  }

  //add the points and vertices to a polydata
  vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);
  polydata->SetVerts(vertices);

  //set vertex (cell) normals
  vtkSmartPointer<vtkDoubleArray> normalsArray =
      vtkSmartPointer<vtkDoubleArray>::New();
  normalsArray->SetNumberOfComponents(3); //3d normals (ie x,y,z)
  normalsArray->SetNumberOfTuples(polydata->GetNumberOfPoints());

  //construct the normal vectors
  double cN1[3] = {1.0, 0.0, 0.0};
  double cN2[3] = {0.0, 1.0, 0.0};
  double cN3[3] = {0.0, 0.0, 1.0};

  //add the data to the normals array
  normalsArray->SetTuple(0, cN1) ;
  normalsArray->SetTuple(1, cN2) ;
  normalsArray->SetTuple(2, cN3) ;

  //add the normals to the cells in the polydata
  polydata->GetCellData()->SetNormals(normalsArray);

  ///////// Get cell normals ///////////
  vtkSmartPointer<vtkDoubleArray> cellNormalsRetrieved =
      vtkDoubleArray::SafeDownCast(polydata->GetCellData()->GetNormals());
  if(cellNormalsRetrieved)
  {
    cout << "There are " << cellNormalsRetrieved->GetNumberOfTuples() << " cell normals." << endl;

    for(vtkIdType i = 0; i < cellNormalsRetrieved->GetNumberOfTuples(); i++)
    {
      double cN[3];
      cellNormalsRetrieved->GetTuple(i, cN);
      cout << "Cell normal " << i << ": " << cN[0] << " " << cN[1] << " " << cN[2] << endl;
    }
  }
  else
  {
    cout << "No cell normals." << endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(PolyDataCellNormals)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(PolyDataCellNormals MACOSX_BUNDLE PolyDataCellNormals.cxx)
 
target_link_libraries(PolyDataCellNormals ${VTK_LIBRARIES})
```

**Download and Build PolyDataCellNormals**

Click [here to download PolyDataCellNormals](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/PolyDataCellNormals.tar) and its *CMakeLists.txt* file.
Once the *tarball PolyDataCellNormals.tar* has been downloaded and extracted,
```
cd PolyDataCellNormals/build 
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
./PolyDataCellNormals
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

