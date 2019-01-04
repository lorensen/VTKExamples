#include <vtkSmartPointer.h>
#include <vtkDenseArray.h>
#include <vtkArrayToTable.h>
#include <vtkTable.h>
#include <vtkArrayData.h>

int main(int, char *[])
{
  vtkSmartPointer<vtkDenseArray<int> > array =
      vtkSmartPointer<vtkDenseArray<int> >::New();
  array->Resize(2,4);

  //set values
  std::cout << "There are " << array->GetExtents()[0].GetEnd() << std::endl;
  std::cout << "There are " << array->GetExtents()[1].GetEnd() << std::endl;

  for(vtkIdType i = 0; i < array->GetExtents()[0].GetEnd(); i++)
  {
    for(vtkIdType j = 0; j < array->GetExtents()[1].GetEnd(); j++)
    {	
      array->SetValue(i, j, i+j);
    }
  }

  vtkSmartPointer<vtkArrayData> arrayData =
    vtkSmartPointer<vtkArrayData>::New();
  arrayData->AddArray(array);

  vtkSmartPointer<vtkArrayToTable> arrayToTable =
    vtkSmartPointer<vtkArrayToTable>::New();
  arrayToTable->SetInputData(arrayData);
  arrayToTable->Update();

  vtkSmartPointer<vtkTable> table = arrayToTable->GetOutput();
  table->Dump();

  return EXIT_SUCCESS;
}
