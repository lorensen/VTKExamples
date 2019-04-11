// vtk includes
#include <vtkDoubleArray.h>
#include <vtkInformation.h>
#include <vtkInformationDoubleVectorKey.h>

// std includes
#include <iostream>

int main(int, char *[]) {

  // create a 2-element array
  vtkSmartPointer<vtkDoubleArray> array =
    vtkSmartPointer<vtkDoubleArray>::New();
  array->SetName("array");
  array->SetNumberOfComponents(1);
  array->SetNumberOfTuples(2);
  array->SetValue(0, 1.);
  array->SetValue(1, 2.);

  // access the info (presently none stored)
  vtkInformation* info = array->GetInformation();

  // add one attribute, a double vector
  const char *name = "myKey";
  const char *location = "MyClass"; // 
  const int length = 3;
  vtkInformationDoubleVectorKey *key = new vtkInformationDoubleVectorKey(name, 
                                                                         location, 
                                                                         length);
  double values[] = {0.1, 0.2, 0.3};
  info->Set(key, values[0], values[1],values[2]);

  // extract the key
  double *vals = info->Get(key);
  std::cout << "extracted values are: " << vals[0] << ", " << vals[1] << ", " << vals[2] << '\n';

  return EXIT_SUCCESS;
}
