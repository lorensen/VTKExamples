#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<double> > array = 
    vtkSmartPointer<vtkDenseArray<double> >::New();
  
  array->Resize(5,5);
  
  array->SetValue(4,4, 5.0);
  
  std::cout << array->GetValue(4,4) << std::endl;
  
  return EXIT_SUCCESS;
}
