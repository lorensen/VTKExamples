[VTKExamples](/home/)/[Cxx](/Cxx)/Utilities/ConstructTable

### Description
This example creates a 3x3 table. The columns MUST be added first - if you attempt to call AddRow type functions, they will not do anything (or produce errors) because the table still has 0 columns until you tell it otherwise. This example adds 3 empty columns to the table, then goes back and fills them in. 

Warning: the table does not copy the data, so if you add the SAME column to the table each time, i.e.
<source lang="cpp">
vtkSmartPointer<vtkVariantArray> col = vtkSmartPointer<vtkVariantArray>::New();

col->InsertNextValue(vtkVariant(0.0));
col->InsertNextValue(vtkVariant(0.0));
col->InsertNextValue(vtkVariant(0.0));
table->AddColumn(Col);
table->AddColumn(Col);
table->AddColumn(Col);
</source>

If you modify one of the entries in the table with  Table->SetValue ( r,c, vtkVariant ( counter ) ); after they have all been set to the same column, the rth entry in EVERY column will be changed.

**ConstructTable.cxx**
```c++
#include <vtkTable.h>
#include <vtkVariant.h>
#include <vtkVariantArray.h>
#include <vtkSmartPointer.h>

int main(int, char *[])
{
  //construct an empty table
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  for ( unsigned int i = 0; i < 3; i++ )
  {
    vtkSmartPointer<vtkVariantArray> col =
      vtkSmartPointer<vtkVariantArray>::New();

    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    table->AddColumn ( col );
  }

  //fill the table with values
  unsigned int counter = 0;
  for(vtkIdType r = 0; r < table->GetNumberOfRows(); r++ )
  {
    for(vtkIdType c = 0; c < table->GetNumberOfColumns(); c++ )
    {
      table->SetValue ( r,c, vtkVariant ( counter ) );
      counter++;
    }
  }

  //print information about the table
  std::cout << "NumRows: " << table->GetNumberOfRows() << std::endl;
  std::cout << "NumCols: " << table->GetNumberOfColumns() << std::endl;

  //display the table
  table->Dump ( 3 );

  //access elements of the table
  for(vtkIdType r = 0; r < table->GetNumberOfRows(); r++ )
  {
    for(vtkIdType c = 0; c < table->GetNumberOfColumns(); c++ )
    {
    vtkVariant v = table->GetValue( r,c);
    std::cout << "(r,c) = (" << r << "," << c << ") = " << v << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConstructTable)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConstructTable MACOSX_BUNDLE ConstructTable.cxx)
 
target_link_libraries(ConstructTable ${VTK_LIBRARIES})
```

**Download and Build ConstructTable**

Click [here to download ConstructTable](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConstructTable.tar) and its *CMakeLists.txt* file.
Once the *tarball ConstructTable.tar* has been downloaded and extracted,
```
cd ConstructTable/build 
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
./ConstructTable
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

