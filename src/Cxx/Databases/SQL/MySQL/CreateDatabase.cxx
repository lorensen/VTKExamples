#include <vtkSmartPointer.h>
#include <vtkMySQLDatabase.h>
#include <vtkSQLQuery.h>
#include <vtkVariant.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkMySQLDatabase> db =
    vtkSmartPointer<vtkMySQLDatabase>::Take(dynamic_cast<vtkMySQLDatabase*>(
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
