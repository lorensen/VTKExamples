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
    vtkSmartPointer<vtkMySQLDatabase>::Take(dynamic_cast<vtkMySQLDatabase*>(
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
