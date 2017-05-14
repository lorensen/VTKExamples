[VTKExamples](/index/)/[Cxx](/Cxx)/Databases/SQL/MySQL/WriteToDatabase

**WriteToDatabase.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>
#include <vtkVariant.h>

int main(int, char *[])
{
  // url syntax:
  // mysql://'[[username[':'password]'@']hostname[':'port]]'/'[dbname]

  vtkSmartPointer<vtkMySQLDatabase> db =
    vtkSmartPointer<vtkMySQLDatabase>::Take(vtkMySQLDatabase::SafeDownCast(
            vtkSQLDatabase::CreateFromURL( "mysql://root@localhost/TestDatabase" ) ));

  bool status = db->Open();

  std::cout << "Database open? " << status << std::endl;

  if(!status)
  {
    return EXIT_FAILURE;
  }

  vtkSmartPointer<vtkSQLQuery> query =
    vtkSmartPointer<vtkSQLQuery>::Take(db->GetQueryInstance());

  std::string createQuery( "INSERT INTO TestTable (PointId) VALUES(8)");
  std::cout << createQuery << std::endl;
  query->SetQuery( createQuery.c_str() );
  query->Execute();

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(WriteToDatabase)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(WriteToDatabase MACOSX_BUNDLE WriteToDatabase.cxx)
 
target_link_libraries(WriteToDatabase ${VTK_LIBRARIES})
```

**Download and Build WriteToDatabase**

Click [here to download WriteToDatabase](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/WriteToDatabase.tar) and its *CMakeLists.txt* file.
Once the *tarball WriteToDatabase.tar* has been downloaded and extracted,
```
cd WriteToDatabase/build 
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
./WriteToDatabase
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

