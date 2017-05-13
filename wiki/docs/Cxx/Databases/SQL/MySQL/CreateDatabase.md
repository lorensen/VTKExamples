[VTKExamples](/index/)/[Cxx](/Cxx)/Databases/SQL/MySQL/CreateDatabase

**CreateDatabase.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>
#include <vtkVariant.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMySQLDatabase> db =
    vtkSmartPointer<vtkMySQLDatabase>::Take(vtkMySQLDatabase::SafeDownCast(
            vtkSQLDatabase::CreateFromURL( "mysql://root@localhost/TestDatabase" ) ));

  bool status = db->Open();

  std::cout << "Database open? " << status << std::endl;

  if(!status)
  {
    //create database
    std::cout << "Database does not exist, create it!" << std::endl;
    db->CreateDatabase("TestDatabase", false);
  }
  else
  {
    std::cout << "Database already exists!" << std::endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(CreateDatabase)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(CreateDatabase MACOSX_BUNDLE CreateDatabase.cxx)
 
target_link_libraries(CreateDatabase ${VTK_LIBRARIES})
```

**Download and Build CreateDatabase**

Click [here to download CreateDatabase](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/CreateDatabase.tar) and its *CMakeLists.txt* file.
Once the *tarball CreateDatabase.tar* has been downloaded and extracted,
```
cd CreateDatabase/build 
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
./CreateDatabase
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

