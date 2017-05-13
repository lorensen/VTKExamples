[VTKExamples](/home/)/[Cxx](/Cxx)/Databases/SQL/MySQL/ConnectAndRead

**ConnectAndRead.cxx**
```c++
#include <vtkSmartPointer.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>
#include <vtkVariant.h>

/*
If you get the error:
Unsupported protocol: mysql
It means you must recompile VTK with VTK_USE_MYSQL = ON

If you get the error:
vtkMySQLDatabase::New() is not defined
It means that cmake did not find your mysql include and library
path correctly (ie.  MYSQL_INCLUDE_DIRECTORIES, etc)
*/

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

  std::string createQuery( "SELECT PointId FROM TestTable");
  std::cout << createQuery << std::endl;
  query->SetQuery( createQuery.c_str() );
  query->Execute();

  for ( int col = 0; col < query->GetNumberOfFields(); ++ col )
  {
    if ( col > 0 )
    {
      cerr << ", ";
    }
    cerr << query->GetFieldName( col );
  }
  cerr << endl;
  while ( query->NextRow() )
  {
    for ( int field = 0; field < query->GetNumberOfFields(); ++ field )
    {
      if ( field > 0 )
      {
        cerr << ", ";
      }
      cerr << query->DataValue( field ).ToString().c_str();
    }
    cerr << endl;
  }

  return EXIT_SUCCESS;
}
```
**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 2.8)
 
PROJECT(ConnectAndRead)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(ConnectAndRead MACOSX_BUNDLE ConnectAndRead.cxx)
 
target_link_libraries(ConnectAndRead ${VTK_LIBRARIES})
```

**Download and Build ConnectAndRead**

Click [here to download ConnectAndRead](https://github.com/lorensen/VTKWikiExamplesTarballs/raw/master/ConnectAndRead.tar) and its *CMakeLists.txt* file.
Once the *tarball ConnectAndRead.tar* has been downloaded and extracted,
```
cd ConnectAndRead/build 
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
./ConnectAndRead
```
**WINDOWS USERS PLEASE NOTE:** Be sure to add the VTK bin directory to your path. This will resolve the VTK dll's at run time.

