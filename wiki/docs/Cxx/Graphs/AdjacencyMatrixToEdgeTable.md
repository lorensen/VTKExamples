[VTKExamples](/index/)/[Cxx](/Cxx)/Graphs/AdjacencyMatrixToEdgeTable

**AdjacencyMatrixToEdgeTable.cxx**
```c++
/* The output is:

10 20 30
40 50 60
70 80 90

+-----------------+------------------+
|                 | value            |
+-----------------+------------------+
| 2               | 30               |
| 1               | 20               |
| 0               | 10               |
| 2               | 60               |
| 1               | 50               |
| 0               | 40               |
| 2               | 90               |
| 1               | 80               |
| 0               | 70               |
+-----------------+------------------+

The first column is the column index of the item in the 'value' column.
The row index is given by the number of times we've previously seen the column index.
For some reason, zeros in the matrix are not reported in the table.

For example, the first row says that the value '30' is in column 2 of the matrix (0-based indexing).
Since we have not previously seen an item in column 2, it is in row 0 of the matrix.

The fourth row says that the value '60' is also in column 2. We infer that '60' is row 1 of the
matrix because we have already seen one item (the '30') in column 2.
*/

#include <vtkSmartPointer.h>
#include <vtkVersion.h>
#include <vtkDenseArray.h>
#include <vtkArrayToTable.h>
#include <vtkTable.h>
#include <vtkArrayData.h>
#include <vtkAdjacencyMatrixToEdgeTable.h>
#include <vtkArrayPrint.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array =
    vtkSmartPointer<vtkDenseArray<double> >::New();

  array->Resize(3,3);

  unsigned int counter = 1;
  for(vtkIdType i = 0; i < array->GetExtents()[0].GetEnd(); i++)
  {
    for(vtkIdType j = 0; j < array->GetExtents()[1].GetEnd(); j++)
    {
      array->SetValue(i, j, counter*10);
      counter++;
    }
  }

  vtkPrintMatrixFormat(std::cout, array.GetPointer());

  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);

  vtkSmartPointer<vtkAdjacencyMatrixToEdgeTable> adjacencyMatrixToEdgeTable =
    vtkSmartPointer<vtkAdjacencyMatrixToEdgeTable>::New();
#if VTK_MAJOR_VERSION <= 5
  adjacencyMatrixToEdgeTable->SetInputConnection(arrayData->GetProducerPort());
#else
  adjacencyMatrixToEdgeTable->SetInputData(arrayData);
#endif
  adjacencyMatrixToEdgeTable->Update();

  adjacencyMatrixToEdgeTable->GetOutput()->Dump();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(AdjacencyMatrixToEdgeTable)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(AdjacencyMatrixToEdgeTable MACOSX_BUNDLE AdjacencyMatrixToEdgeTable.cxx)
 
target_link_libraries(AdjacencyMatrixToEdgeTable ${VTK_LIBRARIES})
```

**Download and Build AdjacencyMatrixToEdgeTable**

Click [here to download AdjacencyMatrixToEdgeTable](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/AdjacencyMatrixToEdgeTable.tar) and its *CMakeLists.txt* file.
Once the *tarball AdjacencyMatrixToEdgeTable.tar* has been downloaded and extracted,
```
cd AdjacencyMatrixToEdgeTable/build 
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
./AdjacencyMatrixToEdgeTable
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

