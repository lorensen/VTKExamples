#include <vtkSmartPointer.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>
#include <vtkVariant.h>

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

  std::string createQuery( "INSERT INTO TestTable (PointId) VALUES(8)");
  std::cout << createQuery << std::endl;
  query->SetQuery( createQuery.c_str() );
  query->Execute();

  return EXIT_SUCCESS;
}
