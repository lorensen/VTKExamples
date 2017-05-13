#include <vtkSmartPointer.h>
#include <vtkFloatArray.h>
#include <vtkIdList.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkFloatArray> distances =
    vtkSmartPointer<vtkFloatArray>::New();
  distances->SetNumberOfComponents(1);
  distances->SetName("Distances");

  distances->InsertNextValue(5);
  distances->InsertNextValue(15);
  distances->InsertNextValue(15);
  distances->InsertNextValue(25);
  distances->InsertNextValue(15);

  // Get first location
  vtkIdType result = distances->LookupValue(15);
  std::cout << "result: " << result << std::endl;

  // Get all locations
  vtkSmartPointer<vtkIdList> idList =
    vtkSmartPointer<vtkIdList>::New();
  distances->LookupValue(15, idList);
  std::cout << "found at: " << std::endl;
  for(vtkIdType i = 0; i < idList->GetNumberOfIds(); i++)
  {
    std::cout << idList->GetId(i) << " ";
  }

  return EXIT_SUCCESS;
}
