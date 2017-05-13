[VTKExamples](/index/)/[Cxx](/Cxx)/InfoVis/DelimitedTextWriter

### Description
Is the output of
<source lang="cpp">
"","",""
0,1,2
3,4,5
6,7,8
</source>

expected? What is the first line indicating? Simply that there are 3 string fields?

With my prior edit, the first line is now "column-0","column-1","column-2" -- the first line is the names of the column arrays in the table. I added them to the example because the example was crashing on Windows builds, where streaming a NULL char* is no bueno. (David Cole)

**DelimitedTextWriter.cxx**
```c++
 #include <vtkVersion.h>

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkDelimitedTextWriter.h>
#include <vtkSphereSource.h>
#include <vtkVariantArray.h>
#include <vtkTable.h>

#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
  std::string outputFilename = "output.txt";

  // Use the specified filename if it is provided
  if(argc == 2)
  {
    outputFilename = argv[1];
  }

  // Construct an empty table
  vtkSmartPointer<vtkTable> table =
    vtkSmartPointer<vtkTable>::New();

  for(unsigned int i = 0; i < 3; i++)
  {
    vtkSmartPointer<vtkVariantArray> col =
      vtkSmartPointer<vtkVariantArray>::New();

    std::ostringstream oss;
    oss << "column-" << i;
    std::string colName = oss.str();
    col->SetName(colName.c_str());

    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    col->InsertNextValue ( vtkVariant ( 0.0 ) );
    table->AddColumn ( col );
  }

  // Fill the table with values
  unsigned int counter = 0;
  for(vtkIdType r = 0; r < table->GetNumberOfRows(); r++ )
  {
    for(vtkIdType c = 0; c < table->GetNumberOfColumns(); c++ )
    {
      table->SetValue ( r,c, vtkVariant ( counter ) );
      counter++;
    }
  }

  vtkSmartPointer<vtkDelimitedTextWriter> writer =
    vtkSmartPointer<vtkDelimitedTextWriter>::New();
  writer->SetFileName(outputFilename.c_str());
#if VTK_MAJOR_VERSION <= 5
  writer->SetInputConnection(table->GetProducerPort());
#else
  writer->SetInputData(table);
#endif
  writer->Write();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(DelimitedTextWriter)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(DelimitedTextWriter MACOSX_BUNDLE DelimitedTextWriter.cxx)
 
target_link_libraries(DelimitedTextWriter ${VTK_LIBRARIES})
```

**Download and Build DelimitedTextWriter**

Click [here to download DelimitedTextWriter](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/DelimitedTextWriter.tar) and its *CMakeLists.txt* file.
Once the *tarball DelimitedTextWriter.tar* has been downloaded and extracted,
```
cd DelimitedTextWriter/build 
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
./DelimitedTextWriter
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

