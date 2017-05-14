#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetName("Distances");
  distances->SetNumberOfComponents(1);
  distances->SetNumberOfValues(5);

  //set values
  for(vtkIdType i = 0; i < distances->GetNumberOfTuples(); i++)
  {
    float f = (float)i + 0.1;
    distances->SetValue(i, f);
  }

  //get values
  for(vtkIdType i = 0; i < distances->GetNumberOfTuples(); i++)
  {
    float f = distances->GetValue(i);
    std::cout << f << std::endl;
  }

  return EXIT_SUCCESS;
}
