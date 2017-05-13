#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>

int main(int, char *[])
{
  // Create an N-D array
  vtkSmartPointer<vtkDenseArray<double> > array = 
      vtkSmartPointer<vtkDenseArray<double> >::New();
  
  // Resize the array to 4x5x3
  array->Resize(4,5,3);
  
  // Set a value
  int i = 0; int j = 0; int k = 0;
  double value = 3.0;
  array->SetValue(i, j, k, value);
  
  // Get a value
  std::cout << array->GetValue(i,j,k) << std::endl;
  
  // Get size (bounds) of whole array
  cout << array->GetExtents() << endl;
  
  // Get size (bounds) of array dimensions
  std::cout << array->GetExtents()[0] << std::endl;
  std::cout << array->GetExtents()[1] << std::endl;
  std::cout << array->GetExtents()[2] << std::endl;
  
  // Get the bounds of the 0th dimension
  std::cout << array->GetExtents()[0].GetBegin() << std::endl;
  std::cout << array->GetExtents()[0].GetEnd() << std::endl;
  
  return EXIT_SUCCESS;
}
