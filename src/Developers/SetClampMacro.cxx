#include <vtkSmartPointer.h>

#include "vtkTestClass1.h"

int main (int argc, char *argv[])
{
  vtkSmartPointer<vtkTestClass> myClass = 
      vtkSmartPointer<vtkTestClass>::New();
  
  myClass->SetValue(1);
  cout << "Tried to set 1: " << myClass->GetValue() << endl;
  
  myClass->SetValue(3);
  cout << "Tried to set 3: " << myClass->GetValue() << endl;
  
  myClass->SetValue(10);
  cout << "Tried to set 10: " << myClass->GetValue() << endl;
  
  return EXIT_SUCCESS;
}
